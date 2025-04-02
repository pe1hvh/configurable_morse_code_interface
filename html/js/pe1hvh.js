
/**
 *      Author : JA van Hernen, PE1HVH
 *        Date : 2025-03-10
 *    Homepage : https://www.pe1hvh.nl/?cursus=morse-multiplatform-interface
 *  Repository : https://github.com/pe1hvh/cw-multiplatform-interface
 * Description : Multiplatform Morse Code Interface for LCWO, PCWFistCheck, VBand etc.
 *
 *  
 * This script sets up event listeners and manages the UI for the Morse Code Interface.
 * It communicates with a Seeeduino XIAO SAMD21 device via SimpleWebSerial for sending and receiving data.
 * 
 * It is the online configurator for the seeeduino cw-multiplatform-interface.
 *
 * The MIT license applies.
 *  
 */
document.addEventListener('DOMContentLoaded', function() {
    // DOM element references
    const typeMorseKeySelect = document.getElementById('typeMorseKey');
    const typeEventSelect = document.getElementById('typeEvent');
    const leftEventSelect = document.getElementById('leftEvent');
    const rightEventSelect = document.getElementById('rightEvent');
    const rightEventRow = document.getElementById('rightEventRow');
    

    /**
     * Set up SimpleWebSerial connection
     */
    const connection = SimpleWebSerial.setupSerialConnection({
        requestAccessOnPageLoad: true,

    });


    /**
     * Handle initial values received from the device
     */
    connection.on("initial_values", initialValues => {
        var jsonObject = JSON.parse(initialValues);
        console.log("Received initial values:", initialValues);  // Debugging
 
        if (typeMorseKey && typeEvent && leftEvent) {
            // Set initial values for form elements
            document.getElementById('typeMorseKey').value = jsonObject[0];
            document.getElementById('typeEvent').value = jsonObject[1];
            // If type of event changes values of leftEvent(pin6) or rightEvent(pin7) also changed
            // therefore is the updateEventOptions.
            updateEventOptions();
            updateRightEventVisibility();
            document.getElementById('leftEvent').value = jsonObject[2];
            document.getElementById('rightEvent').value = jsonObject[3];
          
        } else {
             console.error("One or more elements not found when setting initial values");
        }
    });

    
    /**
     * Handle status updates from the device
     */
    connection.on('status', value => {
        const jsonData = JSON.stringify(value);
        document.getElementById('status').textContent = jsonData;
    });

    
    /**
     * Send button click event handler
     */
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
    
    
    /**
     * Update visibility of right event based on Morse key type
     */ 
    function updateRightEventVisibility() {
        if (typeMorseKeySelect.value === '3') {
            rightEventRow.style.display = 'table-row';
        } else {
            rightEventRow.style.display = 'none';
        }
    }
   
    
    /**
     * Adds an event listener to the 'typeMorseKeySelect' element.
     * The listener triggers the 'updateRightEventVisibility' function whenever
     * the 'change' event occurs. This ensures the visibility of the right event 
     * is updated dynamically based on user interaction.
     */
    typeMorseKeySelect.addEventListener('change', updateRightEventVisibility);
   
    
    /**
     * Update event options based on selected type (mouse or keyboard)
     */
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
    
    /**
     *  Add change event listener for event type
     */
    typeEventSelect.addEventListener('change', updateEventOptions);
    updateEventOptions(); // Initial population of options

    
    /**
     * Get mouse event options
     * @returns {Array} Array of mouse event options
     */
    function getMouseOptions() {
        return [
            { value: 1, text: 'Left Click' },
            { value: 2, text: 'Right Click' },
            { value: 4, text: 'Middle Click' }
        ];
    }
    

    /**
     * Get keyboard event options
     * @returns {Array} Array of keyboard event options
     */
    function getKeyboardOptions() {
        return [
            { value: 128, text: 'Left Control Key' },
            { value: 129, text: 'Left Shift Key' },
            { value: 130, text: 'Left Alt Key' },
            { value: 132, text: 'Right Control Key' },
            { value: 133, text: 'Right Shift Key' },
            { value: 134, text: 'Right Alt Key' },
            { value: 32, text: 'Spacebar' },
            { value: 91, text: '[' },
            { value: 93, text: ']' },
        ];
    }
    
    updateRightEventVisibility(); // Initial visibility check


});