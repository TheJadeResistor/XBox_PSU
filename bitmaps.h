// Images can be converted to XBM format by using the online converter here:
// https://www.online-utility.org/image/convert/to/XBM

// The output must be pasted in a header file, renamed and adjusted to appear
// as as a const unsigned char array in PROGMEM (FLASH program memory).

// The xbm format adds padding to pixel rows so they are a whole number of bytes
// In this example 50 pixel width means 56 bits = 7 bytes
// the 50 height then means array uses 50 x 7 = 350 bytes of FLASH
// The library ignores the padding bits when drawing the image on the display.

// Example of the correct format is shown below

//https://www.online-utility.org/image/convert/to/XBM
//https://filext.com/file-extension/XBM 
//https://www.aconvert.com/image/
//https://www.remove.bg/

// Espressif logo 50 x 50 pixel array in XBM format
#define logoWidth  50  // logo width
#define logoHeight 50  // logo height

// Image is stored in this array
PROGMEM const unsigned char logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x02, 0x80, 0x03, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0xE0, 0x07, 0x00, 
  0x00, 0x00, 0xE0, 0x1E, 0x60, 0x0E, 0x00, 0x00, 0x00, 0x60, 0x18, 0x70, 
  0x0C, 0x00, 0x00, 0x00, 0x60, 0x18, 0x20, 0x18, 0x00, 0x00, 0x00, 0x60, 
  0x18, 0x30, 0x0C, 0x00, 0x00, 0x00, 0x60, 0x18, 0x70, 0x1C, 0x00, 0x00, 
  0x00, 0x60, 0x18, 0x30, 0x0C, 0x00, 0x00, 0x00, 0x60, 0x18, 0x60, 0x08, 
  0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x1C, 0x00, 0x00, 0x00, 0x60, 0x18, 
  0x70, 0x0C, 0x00, 0x00, 0x00, 0x60, 0x18, 0x70, 0x0C, 0x00, 0x00, 0x00, 
  0x60, 0x18, 0x20, 0x18, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x0C, 0x00, 
  0x00, 0x00, 0x60, 0x18, 0x70, 0x1C, 0x00, 0x00, 0x00, 0x60, 0x98, 0x35, 
  0x0C, 0x00, 0x00, 0x00, 0x60, 0xF8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x60, 
  0xFE, 0xFF, 0x1C, 0x00, 0x00, 0x00, 0x60, 0xFE, 0xFF, 0x0D, 0x00, 0x00, 
  0x00, 0xE0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 
  0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 
  0xFF, 0x1F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 
  0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x1F, 0x00, 
  0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 
  0x0F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xE1, 
  0xFF, 0xFF, 0x1F, 0x01, 0x00, 0x00, 0xE6, 0xFF, 0xFF, 0x8F, 0x00, 0x00, 
  0x00, 0xE4, 0xF5, 0x3F, 0xAF, 0x00, 0x00, 0x00, 0xEC, 0xF0, 0x1F, 0x4E, 
  0x00, 0x00, 0x00, 0xE0, 0xF1, 0x1F, 0x1E, 0x00, 0x00, 0x00, 0xE0, 0xF1, 
  0x3F, 0x0F, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 
  0xF8, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0xE4, 0xFF, 0xFF, 0xCF, 0x00, 
  0x00, 0x00, 0xE2, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00,};
