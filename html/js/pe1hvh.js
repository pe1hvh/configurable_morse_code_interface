
document.addEventListener('DOMContentLoaded', function() {


    // --------------------------------------
    // -- Start HTML Inputhandler          --
    // --------------------------------------
    const typeMorseKeySelect = document.getElementById('typeMorseKey');
    const typeEventSelect = document.getElementById('typeEvent');
    const leftEventSelect = document.getElementById('leftEvent');
    const rightEventSelect = document.getElementById('rightEvent');
    const rightEventRow = document.getElementById('rightEventRow');


    //--------------------------------------
    //-- Intialise WebSerial              --
    //--------------------------------------
    //let initialDataLoaded = false;

    const connection = SimpleWebSerial.setupSerialConnection({
        requestAccessOnPageLoad: true,

    });

    //--------------------------------------------------------------------
    //-- Received saved configuration or default values from seeeduino  --
    //--------------------------------------------------------------------
    connection.on("initial_values", initialValues => {
   
   
        var jsonObject = JSON.parse(initialValues);
   
        console.log("Received initial values:", initialValues);  // Debugging
        

        if (typeMorseKey && typeEvent && leftEvent) {
  
            document.getElementById('typeMorseKey').value = jsonObject[0];
            document.getElementById('typeEvent').value = jsonObject[1];
            updateEventOptions();
            document.getElementById('leftEvent').value = jsonObject[2];
            document.getElementById('rightEvent').value = jsonObject[3];
          
        } else {
             console.error("One or more elements not found when setting initial values");
        }
    });
 
    //-------------------------------------
    //-- Received status from seeeduino  --
    //-------------------------------------
    connection.on('status', value => {
        const jsonData = JSON.stringify(value);
        document.getElementById('status').textContent = jsonData;
    });
    

    //---------------------------------------
    //-- Send updated values to seeeduino  --
    //--------------------------------------- 
    document.getElementById('send').addEventListener('click', async () => {
        try {
            
             const  typeMorseKey = document.getElementById('typeMorseKey').value;
             const  typeEvent = document.getElementById('typeEvent').value;
             const  leftEvent = document.getElementById('leftEvent').value;
             const  rightEvent = document.getElementById('rightEvent').value;
  
            let data = {typeMorseKey,typeEvent,leftEvent,rightEvent}; 
            const jsonData = JSON.stringify(data);
            await connection.send("update_values", jsonData);
            document.getElementById('status').textContent = "Send data to Seeeduino!" + jsonData;
        } catch (error) {
            console.error("Error by sending data to Seeeduino: ", error);
        }
    });
    
    
    
    // --------------------------------------------
    // -- Show right event only when key=paddle  --
    // --------------------------------------------
    function updateRightEventVisibility() {
        if (typeMorseKeySelect.value === '3') {
            rightEventRow.style.display = 'table-row';
        } else {
            rightEventRow.style.display = 'none';
        }
    }
    
    typeMorseKeySelect.addEventListener('change', updateRightEventVisibility);
    
    // ---------------------------------------------------------
    // -- Update the Event option when changing the morse key --
    // --------------------------------------------------------- 
    function updateEventOptions() {
        const selectedType = typeEventSelect.value;
        const options = selectedType === '0' ? getMouseOptions() : getKeyboardOptions();
    
        [leftEventSelect, rightEventSelect].forEach(select => {
            select.innerHTML = '';
            options.forEach(option => {
                const optionElement = document.createElement('option');
                optionElement.value = option.value;
                optionElement.textContent = option.text;
                select.appendChild(optionElement);
            });
        });
    }
    
    typeEventSelect.addEventListener('change', updateEventOptions);
    updateEventOptions(); // Initial population of options
    
    // -------------------------------------
    // -- The event options for the Mouse --
    // ------------------------------------- 
    function getMouseOptions() {
        return [
            { value: 1, text: 'Left Click' },
            { value: 2, text: 'Right Click' },
            { value: 4, text: 'Middle Click' }
        ];
    }
    
    // ----------------------------------------
    // -- The event options for the KeyBoard --
    // ---------------------------------------- 
    function getKeyboardOptions() {
        return [
            { value: 128, text: 'Left Control Key' },
            { value: 129, text: 'Left Shift Key' },
            { value: 130, text: 'Left Alt Key' },
            { value: 132, text: 'Right Control Key' },
            { value: 133, text: 'Right Shift Key' },
            { value: 134, text: 'Right Alt Key' }
        ];
    }
    
    updateRightEventVisibility(); // Initial visibility check


});
