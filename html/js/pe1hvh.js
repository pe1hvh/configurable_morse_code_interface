document.addEventListener('DOMContentLoaded', function() {

    //--------------------------------------
    //-- Intialise WebSerial              --
    //--------------------------------------
    
    const connection = SimpleWebSerial.setupSerialConnection({
        requestAccessOnPageLoad: true,
    });
    
    //----------------------------------------
    //-- Load initial values from seeeduino --
    //----------------------------------------
    async function loadInitialData() {
        try {
            const initialValues = await connection.on("get_initial_values");
            
            document.getElementById('typeMorseKey').value = initialValues.typeMorseKey;
            document.getElementById('typeEvent').value = initialValues.typeEvent;
            updateEventOptions(); // Herstel de eventopties op basis van de typeEvent
            document.getElementById('leftEvent').value = initialValues.leftEvent;
            document.getElementById('rightEvent').value = initialValues.rightEvent;
            document.getElementById('status').textContent = initialValues;
        } catch (error) {
            console.error("Error by load of data: ", error);
        }
    }
    
    //---------------------------------------
    //-- Send updated values to seeeduino  --
    //--------------------------------------- 
    document.getElementById('send').addEventListener('click', async () => {
        try {
            const data = {
                typeMorseKey: document.getElementById('typeMorseKey').value,
                typeEvent: document.getElementById('typeEvent').value,
                leftEvent: document.getElementById('leftEvent').value,
                rightEvent: document.getElementById('rightEvent').value
            };
            
            await connection.send("update_values", data);
            document.getElementById('status').textContent = "Send data to Seeeduino!";
        } catch (error) {
            console.error("Error by sending data to Seeeduino: ", error);
        }
    });
    
    
    // --------------------------------------
    // -- Start HTML Inputhandler          --
    // --------------------------------------
    const typeMorseKeySelect = document.getElementById('typeMorseKey');
    const typeEventSelect = document.getElementById('typeEvent');
    const leftEventSelect = document.getElementById('leftEvent');
    const rightEventSelect = document.getElementById('rightEvent');
    const rightEventRow = document.getElementById('rightEventRow');
    
    
    // --------------------------------------------
    // -- Show right event only when key=paddle  --
    // --------------------------------------------
    function updateRightEventVisibility() {
        if (typeMorseKeySelect.value === '2') {
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
            { value: '1', text: 'Left Click' },
            { value: '2', text: 'Right Click' },
            { value: '4', text: 'Middle Click' }
        ];
    }
    
    // ----------------------------------------
    // -- The event options for the KeyBoard --
    // ---------------------------------------- 
    function getKeyboardOptions() {
        return [
            { value: '0x80', text: 'Left Control Key' },
            { value: '0x81', text: 'Left Shift Key' },
            { value: '0x82', text: 'Left Alt Key' },
            { value: '0x84', text: 'Right Control Key' },
            { value: '0x85', text: 'Right Shift Key' },
            { value: '0x86', text: 'Right Alt Key' }
        ];
    }
    
    
    updateRightEventVisibility(); // Initial visibility check
    });