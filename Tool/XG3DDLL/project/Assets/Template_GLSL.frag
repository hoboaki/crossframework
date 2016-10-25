#version auto
// 文字コード：UTF-8
#if defined(GL_ES)
    precision highp float;
#endif

//------------------------------------------------------------------------------
#if defined(_USE_ATTR_NORMAL)
    in vec3 pshNormal;
#endif

#if defined(_USE_ATTR_COLOR0)
    in vec4 pshColor0
#endif

//------------------------------------------------------------------------------
out vec4 oFragColor;

//------------------------------------------------------------------------------
void main()
{
#if defined(_USE_ATTR_COLOR0)
    oFragColor = pshColor0;
#elif defined(_USE_ATTR_NORMAL)
    oFragColor = vec4((normalize(pshNormal) + vec3(1.0)) * 0.5, 1.0);
#else
    oFragColor = vec4(1.0);
#endif
}

//------------------------------------------------------------------------------
// EOF
