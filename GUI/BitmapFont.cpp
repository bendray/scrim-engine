#include "BitmapFont.hpp"
#include <fstream>

CBitmapFont::CBitmapFont(void)
{
}

CBitmapFont::~CBitmapFont(void)
{
}

int CBitmapFont::Load(const char* fontData, const char* fontName)
{
    std::ifstream fin;
    int i;
    char temp;
    
    // Read in the font size and spacing between chars.
    fin.open(fontData);
    if(fin.fail())
    {
        return 1;
    }

    // Read in the 95 used ascii characters for text.
    for(i=0; i<95; i++)
    {
        fin.get(temp);
        while(temp != ' ')
        {
            fin.get(temp);
        }
        fin.get(temp);
        while(temp != ' ')
        {
            fin.get(temp);
        }

        fin >> m_fontData[i].x;
        fin >> m_fontData[i].w;
        if(i == 0) 
            m_fontData[i].size = 6.0f;
        else
            m_fontData[i].size = m_fontData[i].w;
    }

    fin.close();

    return 0;
}
