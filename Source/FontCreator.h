#include "raylib.h"
#include <vector>
#include <string>

class FontCreator {
private:
    // Constructor privado para prevenir instanciación directa
    FontCreator() {}

    // Eliminar el constructor por copia y la asignación
    FontCreator(const FontCreator&) = delete;
    FontCreator& operator=(const FontCreator&) = delete;

public:
    static FontCreator& GetInstance() {
        static FontCreator instance; // Instancia única, creada la primera vez
        return instance;
    }


    Font CreateFontFromTexture(Texture2D texture, int charWidth, int charHeight,
        const std::vector<int>& codepoints, int padding = 0) {

        int charsPerRow = texture.width / charWidth; 
        int charsPerColumn = texture.height / charHeight;

        int glyphCount = codepoints.size();
        if (glyphCount > charsPerRow * charsPerColumn) {
            TraceLog(LOG_WARNING, "Not enough space in the texture to fit all codepoints");
            glyphCount = charsPerRow * charsPerColumn;
        }

        GlyphInfo* glyphs = new GlyphInfo[glyphCount];
        Rectangle* recs = new Rectangle[glyphCount];

        for (int i = 0; i < glyphCount; i++) {
            int x = (i % charsPerRow) * charWidth;
            int y = (i / charsPerRow) * charHeight;

            recs[i] = { (float)x, (float)y, (float)charWidth, (float)charHeight };

            glyphs[i].value = codepoints[i]; 
            glyphs[i].offsetX = 0;        
            glyphs[i].offsetY = 0;     
            glyphs[i].advanceX = charWidth + padding;
            glyphs[i].image = GenImageColor(charWidth, charHeight, BLANK);
        }

        Font customFont = { 0 };
        customFont.baseSize = charHeight;
        customFont.glyphCount = glyphCount;
        customFont.glyphPadding = padding;
        customFont.texture = texture;
        customFont.glyphs = glyphs;
        customFont.recs = recs;

        return customFont;
    }

    // Destroy a created font
    void DestroyFont(Font& font) {
        delete[] font.recs; // Free the recs array

        for (int i = 0; i < font.glyphCount; i++) {
            UnloadImage(font.glyphs[i].image); 
        }
        delete[] font.glyphs;
    }

    // Destructor
    ~FontCreator() {}
};
