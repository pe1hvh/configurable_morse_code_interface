document.addEventListener('DOMContentLoaded', function() {
    const typeMorseKeySelect = document.getElementById('typeMorseKey');
    const typeEventSelect = document.getElementById('typeEvent');
    const leftEventSelect = document.getElementById('leftEvent');
    const rightEventSelect = document.getElementById('rightEvent');

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

    function getMouseOptions() {
        return [
            { value: '0', text: 'Left Click' },
            { value: '1', text: 'Right Click' },
            { value: '2', text: 'Middle Click' }
        ];
    }

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

    typeEventSelect.addEventListener('change', updateEventOptions);

    // Function to set values from Seeeduino
    function setValuesFromSeeeduino(data) {
        typeEventSelect.value = data.typeEvent;
        typeMorseKeySelect.value = data.typeMorseKey;
        
        updateEventOptions(); // Update options based on typeEvent

        leftEventSelect.value = data.leftEvent;
        rightEventSelect.value = data.rightEvent;
    }

    // Example of how to use setValuesFromSeeeduino
    document.getElementById('connect').addEventListener('click', async () => {
        try {
            device = await navigator.usb.requestDevice({
                filters: [{ vendorId: 0x2886 }] // Seeed Studio Vendor ID
            });
            await device.open();
            await device.selectConfiguration(1);
            await device.claimInterface(0);
            document.getElementById('status').textContent = 'Connected with XIAO';

            // After connecting, request current values from Seeeduino
            await requestCurrentValues();
        } catch (error) {
            console.error('Error connection:', error);
        }
    });

    async function requestCurrentValues() {
        if (!device) {
            console.error('Device not connected');
            return;
        }

        try {
            // Send a command to request current values
            await device.transferOut(1, new Uint8Array([0xFF])); // 0xFF could be your "request values" command

            // Receive the values
            const result = await device.transferIn(1, 64);
            const data = new Uint8Array(result.data.buffer);

            // Assuming the data is sent in the order:  typeMorseKey, typeEvent, leftEvent, rightEvent
            setValuesFromSeeeduino({
                typeMorseKey: data[1].toString(),
                typeEvent: data[0].toString(),
                leftEvent: data[2].toString(16), // Convert to hex string for keyboard events
                rightEvent: data[3].toString(16) // Convert to hex string for keyboard events
                });
        } catch (error) {
            console.error('Error requesting current values:', error);
        }
    }

    updateEventOptions(); // Initial population of options
});

