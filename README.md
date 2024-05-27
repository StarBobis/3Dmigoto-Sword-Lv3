# Archived
This project is stop developed and transfer all code into my MigotoModToo project,and keep developing it there, so this repository now turn into archived.


# 3Dmigoto-Sword
Extract .ib and .vb format 3D model from 3Dmigoto buffer files.

A gift for all 3Dmigoto mod author, happy new year 2024!

![image](https://github.com/StarBobis/3Dmigoto-Sword-Lv3/assets/151726114/03c73d23-4e14-421f-a8b9-18ec7155bd2d)

# Feature
- Support every d3d11 mod type of GI,HI3,HSR,ZZZ,NBP
- Designed with a GUI and reverse CLI program writen in C++ ,very simple to use,and extremely fast to reverse.
- Log supported.

# Tutorial
tutorial for how to use see https://youtu.be/F2EQLG6Xw_A

# How to Build 
Some preconfig you will need to have:
- VisualStudio 2022  VS143toolset.
- Install Boost 1.84.0


initialize boost config:
```.\bootstrap.bat```

build boost: 

```.\b2.exe variant=release link=static runtime-link=static threading=multi runtime-debugging=off```


- GUI use WinForm and .Net v4.7.2 ,see: https://github.com/StarBobis/3Dmigoto-Sword-GUI

# ThirdParty Used
- Json for morden C++ https://github.com/nlohmann/json/
- easylogpp https://github.com/amrayn/easyloggingpp/

# Acknowledgement
- Great thanks for SilentNightSound for GIMI project and his original reverse scripts.
- Great thanks to 자연풍경 for reverse POC and his C# single mod ini parse code.
- Great thanks to a unknown ProModder in AGMG for test and merged.ini parse py scripts.
- Great thanks to Звездный Мираж and Песчаный for offer the original C++ reverse code design.

# Discord
Server invite link: https://discord.gg/Cz577BcRf5

If you find any 3Dmigoto mod can't be reverse, contact me or open a issue with mod file in attachment and I will fix the problem as soon as I can.
