#version auto
// 文字コード：UTF-8
//------------------------------------------------------------------------------
in vec3 _attrPosition;

// Normal
#if defined(USE_ATTR_NORMAL)
    in vec3 _attrNormal;
#endif

// Color0
#if defined(USE_ATTR_COLOR0)
    in vec4 _attrColor0;
#endif

// TexCoord0
#if defined(USE_ATTR_TEX_COORD0)
    in vec2 _attrTexCoord0;
#endif

//------------------------------------------------------------------------------
uniform mat4 _prmMtxProj;
uniform mat4 _prmMtxView;
uniform mat4 _prmMtxWorld;

//------------------------------------------------------------------------------
#if defined(USE_ATTR_NORMAL)
    out vec3 pshNormal;
#endif

#if defined(USE_ATTR_COLOR0)
    out vec4 pshColor0;
#endif

//------------------------------------------------------------------------------
void main()
{
#if defined(USE_ATTR_NORMAL)
    pshNormal = _attrNormal;
#endif
#if defined(USE_ATTR_COLOR0)
    pshColor0 = _attrColor0;
#endif

    {// Position
        vec4 pos4 = vec4(_attrPosition, 1.0);
        gl_Position =  _prmMtxProj * _prmMtxView * _prmMtxWorld * pos4;
    }
}

//------------------------------------------------------------------------------
// EOF
