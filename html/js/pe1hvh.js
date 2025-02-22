const connection = SimpleWebSerial.setupSerialConnection({
        requestAccessOnPageLoad: true,
 });
 
 
document.getElementById('connect').addEventListener('click', async () => {
    try {
        await connection.connect();
        console.log('Connected successfully');
        connection.send('get_initial_values');
    } catch (error) {
        console.error('Connection failed:', error);
    }
});

connection.on('initial_values', (data) => {
    // Update UI with received data
    document.getElementById('typeMorseKey').value = data.typeMorseKey;
    document.getElementById('typeEvent').value = data.typeEvent;
    updateEventOptions(data.typeEvent);
    document.getElementById('leftEvent').value = data.leftEvent;
    document.getElementById('rightEvent').value = data.rightEvent;
});


function sendConfiguration() {
    const config = {
        typeMorseKey: document.getElementById('typeMorseKey').value,
        typeEvent: document.getElementById('typeEvent').value,
        leftEvent: document.getElementById('leftEvent').value,
        rightEvent: document.getElementById('rightEvent').value
    };
    connection.send('setConfiguration', config);
}

document.getElementById('typeEvent').addEventListener('change', (e) => {
    updateEventOptions(e.target.value);
});

function updateEventOptions(eventType) {
    const leftEvent = document.getElementById('leftEvent');
    const rightEvent = document.getElementById('rightEvent');
    const rightEventContainer = document.getElementById('rightEventContainer');
    
    leftEvent.innerHTML = '';
    rightEvent.innerHTML = '';
    
    const options = eventType === '0' ? 
        getMouseOptions(): getKeyboardOptions();
    
    options.forEach((option, index) => {
        leftEvent.add(new Option(option, index));
        rightEvent.add(new Option(option, index));
    });

    // Toon of verberg het rightEvent op basis van de geselecteerde typeMorseKey
    const typeMorseKey = document.getElementById('typeMorseKey').value;
    rightEventContainer.style.display = typeMorseKey === '2' ? 'block' : 'none';
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
// Voeg een event listener toe voor typeMorseKey
document.getElementById('typeMorseKey').addEventListener('change', () => {
    updateEventOptions(document.getElementById('typeEvent').value);
});


