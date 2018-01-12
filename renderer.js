/* renderer.js */

const electron = require('electron');
const {ipcRenderer} = electron;

// log in button click event handler
function loginButtonClicked(e)
{
    // grab text in username text box
    var usernameInput = document.querySelector('#username-input').value;
    var invalidUsername = document.querySelector('div#invalid');

    invalidUsername.textContent = "";
    
    // check if text box is empty
    if(usernameInput.length < 1)
    {
        invalidUsername.textContent = 'Username cannot be empty.';
    }

    else
    {
        // check username for spaces
        if(usernameInput.indexOf(" ") > -1)
        {
            invalidUsername.textContent = 'Username cannot contain spaces.';
        }

        // username is valid
        else
        {
            /*             TODO           */
            /*                            */
            /*   Send username to server  */
            /* Have server store username */
            /*   and map it to user's IP  */
            /*                            */

            ipcRenderer.send('login-button-success');
        }
    }
}