<div align="center">
<h1 id="roblox-mouse-fix">UWP Mouse Fix 🐭</h1>
<img src="https://img.shields.io/github/downloads/Roblox-Thot/UWPMouseFix/total.svg?style=for-the-badge"> <img src="https://img.shields.io/github/downloads/Roblox-Thot/UWPMouseFix/latest/total?style=for-the-badge&label=Downloads%20For%20Latest"> <br>
<img alt="GitHub commits since latest release (by SemVer including pre-releases)" src="https://img.shields.io/github/commits-since/Roblox-Thot/UWPMouseFix/latest?style=for-the-badge&label=Commits%20Since%20Latest"> <img src="https://img.shields.io/github/last-commit/Roblox-Thot/UWPMouseFix?style=for-the-badge">
</div>

<details>
  <summary>Example of WebSocket Mode</summary>
  <blockquote>

https://github.com/Roblox-Thot/UWPMouseFix/assets/67937010/752da74e-f503-44f8-b787-12e8cca23ede

  </blockquote>
</details>


## Usage
1. Download the zip by downloading the [latest zip](https://github.com/Roblox-Thot/microsoftrbx-cursor-fix/releases/latest)
2. Extract the zip and rename `config.example.ini` to `config.ini`
3. Open the file `MicrosoftRBX-CursorFix.exe`.
4. Open `Roblox` from Microsoft Store.
5. Click some where on roblox to continue.
6. Wait for the HWND scan and pop up the `Enabled` status.
7. To toggle press `INSERT` key.

## Anti Cheat
- **This application is completely harmless for `Roblox` because it has no injection and won't touch the `Roblox` process, this is just keeping mouse position on the same place.**

## FAQ
1. **Why is anti virus detecting it?**
- It shouldn't because the application just sets the mouse to prevent moving out the window of Roblox.
- But if you can find out what is causing like 2 AV to flag it that would be dope

2. **How to turn it on or off?**
- Press `INSERT` key or what ever you set to turn on and off.

3. **Why is it stopped working?**
- Try reopening it, because it might be some issue or bug.

4. **How do i uninstall CursorFix?**
- Simply just by closing the application and deleting it.

5. **Will the keybind support multi-key keybinds?**
- Lmao na I'm way to lazy to add support for that.  Feel free to add code to do it tho its prob not hard.

6. **How is this diffrent from [mengdeveloper's version](https://github.com/mengdeveloper/microsoftrbx-cursor-fix)?***
- This one has
  * Right click lock
  * Auto grabs new roblox windows
  * Websocket mode
  * Config editor
  * Keybind editor (in config file not built-in yet)
  * And soon more?

<div align="center">
<h1 id="roblox-mouse-fix">How to build</h1>
</div>
<details>
  <summary>click to expand</summary>
  <blockquote>
    To build you will need to download <a href="https://github.com/brofield/simpleini">simpleini</a> and import SimpleIni.h and ConvertUTF.h into a Lib folder<br>
    and setup <a href="https://www.boost.org/">Boost Library</a> if you want to build the Websocket script (else just remove all WS shit)<br>
    It should then be able to build.<br>
    If you want the blank config its at <a href="/config.example.ini">config.example.ini</a><br>
  </blockquote>
</details>

## Todo Statuses (once 100% new build will come out)
- Built-in config editor (In build 1.0.4 without ToggleKey)
  - [ ] Edit for ToggleKey 
  - [ ] Replace the Window name check with a Window file check (fix for fluster/any custom names)
  - [x] Edit for LeftBorder
  - [x] Edit for RightBorder
  - [x] Edit for TopBorder
  - [x] Edit for BottomBorder

- Webhook mode (on pause till a way to connect comes out)
  - [x] Add webhook
  - [x] Add loop to wach for changes
  - [x] Make the script for Roblox
  - [x] Upload to GH and make a Build
