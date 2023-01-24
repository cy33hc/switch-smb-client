# switch-ftp-client

Simple FTP client for the switch

![Preview](/screenshot.jpg)

## Installation
Copy the **switch-ftp-client.nro** in to the folder **/switch/switch-ftp-client** of the SD card and then install the **switch-ftp-client.nsp**

## Controls
```
X - Menu (after a file is selected)
A - Select Button/TextBox
B - Un-Select the file list to navigate to other widgets
Y - Mark file(s)/folder(s) for Delete/Rename/Upload/Download
R1 - Navigate to the Remote list of files
L1 - Navigate to the Local list of files
+ - Exit Application
```

## Multi Language Support
The appplication support following languages

The following languages are auto detected.
```
Dutch
English
French
German
Italiano
Japanese
Korean
Polish
Portuguese_BR
Russian
Spanish
Simplified Chinese
Traditional Chinese
```

The following aren't standard languages supported by the switch, therefore requires a config file update.
```
Catalan
Croatian
Euskera
Galego
Hungarian
Indonesian
Ryukyuan
```
User must modify the file **/switch/switch-ftp-client/config.ini** and update the **language** setting to with the **exact** values from the list above.

**HELP:** There are no language translations for the following languages, therefore not support yet. Please help expand the list by submitting translation for the following languages. If you would like to help, please download this [Template](https://github.com/cy33hc/switch-ftp-client/blob/master/lang/English.ini), make your changes and submit an issue with the file attached.
```
Greek
Finnish
Swedish
Danish
Norwegian
Turkish
Arabic
Czech
Romanian
Thai
Vietnamese
```
or any other language that you have a traslation for.

## Credits
Thx to the author of the imgui_decko3d_example which I used as a base to create this app.
https://github.com/scturtle/imgui_deko3d_example

The color theme was borrowed from NX-Shell.
