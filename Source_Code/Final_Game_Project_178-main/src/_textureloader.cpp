#include "_textureloader.h"

map<string, GLuint> _textureLoader::textureCache;

_textureLoader::_textureLoader()
{
    tex = 0;
    width = 0;
    height = 0;
    image = NULL;
}

_textureLoader::~_textureLoader()
{
}

void _textureLoader::loadTexture(char* fileName)
{
    if(!fileName)
    {
        tex = 0;
        return;
    }

    string key(fileName);

    if(textureCache.count(key))
    {
        tex = textureCache[key];
        return;
    }

    image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image)
    {
        cout << "ERROR: Image File not Loaded: " << fileName << endl;
        tex = 0;
        return;
    }

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    image = NULL;

    glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textureCache[key] = tex;
}

void _textureLoader::BindTexture()
{
    if(tex)
        glBindTexture(GL_TEXTURE_2D, tex);
}
