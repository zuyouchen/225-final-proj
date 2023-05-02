@echo off

:start
cls

set python_ver=36

pip install numpy
pip install scipy
pip install PySimpleGUI
pip install mplcursors
pip install matplotlib


python visualization.py


pause
exit



