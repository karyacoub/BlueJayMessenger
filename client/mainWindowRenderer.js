/* maniWindowRenderer.js */

const electron = require('electron');
const {ipcRenderer} = electron;

// prevent enter key from submiting form
var messageForm = document.querySelector('#message-form');
messageForm.addEventListener('submit', function(e){
    // don't submit form by default
    e.preventDefault();

    // instead, call the send button click event handler
    sendButtonClicked();
});

// send button click event handler
function sendButtonClicked()
{
    // grab iframe for messages to be placed in
    var iframeDoc = document.querySelector('iframe').contentWindow.document;

    // grab text from message textbox
    var messageTextBox = document.querySelector('#message-input');
    var message = messageTextBox.value;

    messageTextBox.value = "";

    if(message != "")
    {
        // create new list element
        var li = iframeDoc.createElement('li');
        li.id = 'message-wrapper';
        li.className = 'speech-bubble';

        // create text node, insert into the list element
        var liText = iframeDoc.createTextNode(message);
        li.appendChild(liText);

        // create empty li element to be inserted as a placeholder to start a new column
        var templi = iframeDoc.createElement('li');
        templi.id = 'temp-message-wrapper';

        // grab ul element for li to be placed in
        var ul = (iframeDoc.getElementsByClassName('right'))[0].childNodes[1];

        ul.appendChild(li);

        li.scrollIntoView();

        ipcRenderer.send('message-sent', message);
    }
}

function messageRecieved(data)
{
    console.log(data);
}