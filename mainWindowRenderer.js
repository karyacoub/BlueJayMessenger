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

    // create new list element
    var li = iframeDoc.createElement('li');
    li.id = 'message-wrapper';

    // create text node to be inserted in the list element
    var liText = iframeDoc.createTextNode(message);
    li.appendChild(liText);

    // grab ul element for li to be placed in
    var ul = iframeDoc.querySelector('#messages-list');
    ul.appendChild(li);

    // create and append line break to html
    var br = iframeDoc.createElement('br');
    ul.appendChild(br);

    br.scrollIntoView();
}