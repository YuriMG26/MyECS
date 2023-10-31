@echo off
for /r src %%i in (*.o) do (
    del "%%i"
)
