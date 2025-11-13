# https://github.com/RitoShark/TexThumbnailProvider 
## INSTALL GUISAIS TEX THUMBNAIL PROVIDER FOR THE FILE EXPLORER

originally made and edited by guisai, finished by frog

# Photoshop TEX Plugin

A Photoshop plugin for loading and saving League of Legends `.tex` texture files with DXT5 compression.

This is a fork of Intel's discontinued Texture Works Plugin, modified to support the TEX file format used by League of Legends and other Riot Games titles.

---

## ⚡ Quick Start (Users)

### Installation

1. **Download** the latest release from the [Releases](../../releases) page
2. **Copy** `TexPlugin.8bi` to your Photoshop Plug-ins folder:
   ```
   C:\Program Files\Adobe\Adobe Photoshop [VERSION]\Plug-ins\File Formats\
   ```
3. **Restart** Photoshop

### Usage

**Opening TEX files:**
- `File > Open` and select a `.tex` file
- Or `File > Open As` and choose "TEX Format"

**Saving TEX files:**
- `File > Save As`
- Choose "TEX Format" as the file type
- Files are automatically saved with DXT5 compression

---

## 🛠️ Building from Source

### Prerequisites

- **Windows 7/8/10/11** (32-bit or 64-bit)
- **Visual Studio 2012 or newer** (2022 recommended)
- **Adobe Photoshop CS6 SDK** - [Download from Adobe](http://www.adobe.com/devnet/photoshop/sdk.html)
- **Intel® ISPC Compiler** - [Download from GitHub](https://github.com/ispc/ispc/releases)
- **Adobe Photoshop CS6 or newer** (for testing)

### Setup Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/RitoShark/Photoshop-Tex-Plugin.git
   cd Photoshop-Tex-Plugin
   ```

2. **Download and install the Adobe Photoshop CS6 SDK:**
   - Extract it to a location on your computer
   - Note the path (e.g., `C:\SDK\adobe_photoshop_cs6_sdk_win`)

3. **Download Intel ISPC compiler:**
   - Download `ispc.exe` from the releases page
   - Copy `ispc.exe` to `3rdParty\Intel\Tools\` directory

4. **Set up environment variable:**
   
   **Option A: Using System Environment Variable (Recommended)**
   ```powershell
   # PowerShell (Run as Administrator)
   [Environment]::SetEnvironmentVariable("PHOTOSHOP_SDK_CS6", "C:\path\to\adobe_photoshop_cs6_sdk_win", "User")
   ```
   
   **Option B: Using 8.3 short path (if path has spaces)**
   ```powershell
   # Get short path
   cmd /c for %A in ("C:\Path With Spaces\adobe_photoshop_cs6_sdk_win") do @echo %~sA
   # Use the output (e.g., C:\PATHWI~1\ADOBE_~1) as your PHOTOSHOP_SDK_CS6 value
   ```

5. **Build the plugin:**
   ```powershell
   # Open PowerShell in the project directory
   $env:PHOTOSHOP_SDK_CS6 = "C:\path\to\adobe_photoshop_cs6_sdk_win"
   & "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" IntelTextureWorks.sln /p:Configuration=Release /p:Platform=x64
   ```

6. **Output location:**
   ```
   Plugins\x64\TexPlugin.8bi
   ```

### Debugging

To debug the plugin in Visual Studio:

1. Set `IntelTextureWorks` as the startup project
2. Right-click project → Properties → Debugging
3. Set "Command" to your Photoshop executable:
   ```
   C:\Program Files\Adobe\Adobe Photoshop 2020\Photoshop.exe
   ```
4. Press F5 to start debugging

Debug logs are written to: `C:\temp\IntelTextureWorks_debug.log`

---

## 📋 Features

✅ **Load TEX files** - Supports DXT1, DXT5, and BGRA8 formats  
✅ **Save TEX files** - Automatic DXT5 compression  
✅ **Mipmap support** - Reads mipmapped textures  
✅ **Alpha channels** - Full transparency support  
✅ **No dialogs** - Fast, instant saving with sensible defaults  

---

## 🔧 Technical Details

### Supported TEX Formats

- **DXT1** (0xA) - RGB compression, no alpha
- **DXT5** (0xC) - RGBA compression with alpha
- **BGRA8** (0x14) - Uncompressed 32-bit RGBA

### TEX File Structure

```
Header (12 bytes):
  - Magic: "TEX\0" (4 bytes)
  - Width: uint16 (2 bytes)
  - Height: uint16 (2 bytes)
  - Unknown1: uint8 (1 byte)
  - Format: uint8 (1 byte) - 0xA=DXT1, 0xC=DXT5, 0x14=BGRA8
  - Unknown2: uint8 (1 byte)
  - Has Mipmaps: bool (1 byte)
Pixel Data:
  - Compressed DXT data (size varies)
```

### Export Behavior

- All TEX files are saved with **DXT5 compression** for maximum compatibility
- No mipmaps are generated during export (base texture only)
- Save dialog is skipped for faster workflow

---

## 📝 License

This project is licensed under the **Apache License 2.0** - see [LICENSE](LICENSE) file for details.

### Third-Party Licenses

- **Intel Texture Works** (Original base) - Apache 2.0
- **DirectXTex** - MIT License (Microsoft)
- **Intel ISPC Texture Compressor** - Apache 2.0

**Note:** The Adobe Photoshop SDK is NOT included and must be obtained separately from Adobe under their own licensing terms.

---

## ⚠️ Disclaimer

This project is not affiliated with, endorsed by, or sponsored by:
- **Riot Games, Inc.** (League of Legends)
- **Adobe Systems Incorporated** (Photoshop)
- **Intel Corporation** (Original plugin)

League of Legends and Riot Games are trademarks of Riot Games, Inc.  
Photoshop is a trademark of Adobe Systems Incorporated.

---

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

### Development Notes

- The main plugin code is in `IntelCompressionPlugin/IntelPlugin.cpp`
- TEX format handling is in the `DoReadStart()` and `DoWriteDDS()` functions
- PiPL resource definition is in `IntelCompressionPlugin/IntelPlugin.r`

---

## 📚 Resources

- [Original Intel Texture Works Plugin](https://github.com/GameTechDev/Intel-Texture-Works-Plugin) (Discontinued)
- [Adobe Photoshop SDK Documentation](http://www.adobe.com/devnet/photoshop/sdk.html)
- [DirectXTex Library](https://github.com/Microsoft/DirectXTex)
- [Intel ISPC](https://github.com/ispc/ispc)

---

## 🎮 Credits
- **GUISAI** https://github.com/GuiSaiUwU
- **Original Intel Texture Works Plugin** - Intel Corporation (Discontinued)
- **TEX format support** - RitoShark
- **DirectXTex** - Microsoft Corporation
- **Intel ISPC Texture Compressor** - Intel Corporation

---

**Made with ❤️ for the League of Legends modding community**
