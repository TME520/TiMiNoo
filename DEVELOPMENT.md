# Development tips and tricks

## Convert images to XBM
1. Load your picture into Gimp
2. Convert it into a indexed bitmap, 2 levels, black & white (`Image | Mode | Indexed...`)
3. Export as XBM (`.xbm` extension)
4. Open XBM file and copy/paste its content in source file
5. Add U8G_PROGMEM after variable name (`static unsigned char u8g_logo_bits[] U8G_PROGMEM = { [...] }`)
6. Display the picture: `u8g.drawXBMP( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);`
