# Deploy Release Application

## Windows

Open Qt x.x.x (MinGW ...) and run:

```
windeployqt --no-translations --release --qmldir C:/projects/expander/expander-ui/ExpanderUi/ui/ C:/projects/expander/expander-ui/ExpanderUi/build/Desktop_Qt_6_7_1_MinGW_64_bit-Release\IntExp.exe

```

---

## Linux
1) Build Release app in QtCreator

2) Run App in QtCreator once

3) Install tool dependencies
    ```
    sudo apt update
    sudo apt install patchelf
    ```   

4) Run linux_deploy.py
