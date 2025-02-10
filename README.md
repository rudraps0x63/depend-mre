Run one of the shell scripts: `run-windows.ps1` on Windows, `run-linux.sh` on Linux (make sure to be in the toplevel directory of the repo).

NOTE: In `test.js`, the library being requested for opening must match with the platform
otherwise uncomment the needed one and re-run `bare test.js`
```js
lib.openLibrary("./b/prebuilds/win32-x64/b.bare");
// lib.openLibrary("./b/prebuilds/linux-x64/b.bare");
```
