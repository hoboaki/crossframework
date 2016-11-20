#version auto
// 文字コード：UTF-8
//------------------------------------------------------------------------------
in vec3 _attrPosition;

// Normal
#if defined(_USE_ATTR_NORMAL)
    in vec3 _attrNormal;
#endif

// Tangent
#if defined(_USE_ATTR_TANGENT)
    in vec3 _attrTangent;
#endif

// SkinMtxIdx
#if defined(_USE_ATTR_SKIN_MTX_INDEX)
    in ivec4 _attrSkinMtxIndex;
#endif

// SkinWeight
#if defined(_USE_ATTR_SKIN_WEIGHT)
    in vec4 _attrSkinWeight;
#endif

// Color0
#if defined(_USE_ATTR_COLOR0)
    in vec4 _attrColor0;
#endif

// TexCoord0
#if defined(_USE_ATTR_TEX_COORD0)
    in vec2 _attrTexCoord0;
#endif

//------------------------------------------------------------------------------
uniform mat4 _prmMtxProj;
uniform mat4 _prmMtxView;
uniform mat4 _prmMtxWorld;
#if defined(_USE_ATTR_SKIN_MTX_INDEX)
    uniform vec4 _prmMtxBonePosArray[64 * 3];
#endif
#if defined(_USE_ATTR_SKIN_MTX_INDEX) && defined(_USE_ATTR_NORMAL)
    uniform vec4 _prmMtxBoneNrmArray[64 * 3];
#endif

//------------------------------------------------------------------------------
#if defined(_USE_ATTR_NORMAL)
    out vec3 pshNormal;
#endif

#if defined(_USE_ATTR_TANGENT)
    //out vec3 pshTangent;
#endif

#if defined(_USE_ATTR_COLOR0)
    out vec4 pshColor0;
#endif

//------------------------------------------------------------------------------
/// 4列3行の行列に変換。
#define ToMtx4x3(aRow0, aRow1, aRow2) \
    mat4x3( \
        vec3(aRow0[0], aRow1[0], aRow2[0]), \
        vec3(aRow0[1], aRow1[1], aRow2[1]), \
        vec3(aRow0[2], aRow1[2], aRow2[2]), \
        vec3(aRow0[3], aRow1[3], aRow2[3]) \
        )

//------------------------------------------------------------------------------
/// 3列3行の行列に変換。
#define ToMtx3x3(aRow0, aRow1, aRow2) \
    mat3x3( \
        vec3(aRow0[0], aRow1[0], aRow2[0]), \
        vec3(aRow0[1], aRow1[1], aRow2[1]), \
        vec3(aRow0[2], aRow1[2], aRow2[2]) \
        )

//------------------------------------------------------------------------------
void main()
{
    // Position Normal Tangent
    vec4 position4;
    vec3 normal3;
    vec3 tangent3;
#if defined(_USE_ATTR_SKIN_MTX_INDEX)
    {// Skinning
        ivec4 boneIndexVec = _attrSkinMtxIndex;
        vec4 boneWeightVec = _attrSkinWeight;
        vec3 position = vec3(0);
        vec3 normal = vec3(0);
        vec3 tangent = vec3(0);
        for(int skinSrcIdx = 0; skinSrcIdx < 4; skinSrcIdx++) {
            // Position
            float boneWeight = boneWeightVec.x;
            int boneIndex = boneIndexVec.x;
            int boneBaseIndex = boneIndex * 3;
            mat4x3 boneMatrix = ToMtx4x3(
                _prmMtxBonePosArray[boneBaseIndex],
                _prmMtxBonePosArray[boneBaseIndex + 1],
                _prmMtxBonePosArray[boneBaseIndex + 2]
                );
            position += (boneMatrix * vec4(_attrPosition, 1.0)).xyz * boneWeight;

            // Normal & Tangent
            {
            #if defined(_USE_ATTR_NORMAL)
                mat3 boneItMatrix = ToMtx3x3(
                    _prmMtxBoneNrmArray[boneBaseIndex],
                    _prmMtxBoneNrmArray[boneBaseIndex + 1],
                    _prmMtxBoneNrmArray[boneBaseIndex + 2]
                    );    
                normal += boneItMatrix * _attrNormal * boneWeight;
            #endif
            #if defined(_USE_ATTR_TANGENT)
                tangent += boneItMatrix * _attrTangent * boneWeight;
            #endif
            }

            // ローテーション
            boneIndexVec = boneIndexVec.yzwx;
            boneWeightVec = boneWeightVec.yzwx;
        }

        // Store
        position4 = vec4(position, 1.0);
        {
        #if defined(_USE_ATTR_NORMAL)
            normal3 = normalize(normal);
        #endif
        #if defined(_USE_ATTR_TANGENT)
            tangent3 = normalize(tangent);
        #endif
        }
    }
#else
    // Not Skinning 
    position4 = _prmMtxWorld * vec4(_attrPosition, 1.0);
    {
    #if defined(_USE_ATTR_NORMAL)
        normal3 = _attrNormal;
    #endif
    #if defined(_USE_ATTR_TANGENT)
        tangent3 = _attrTangent;
    #endif
    }
#endif

    // Color
#if defined(_USE_ATTR_COLOR0)
    pshColor0 = _attrColor0;
#endif

    // Output
    {
    #if defined(_USE_ATTR_NORMAL)
        pshNormal = mat3(_prmMtxView) * normal3;
    #endif
    #if defined(_USE_ATTR_TANGENT)
        //pshTangent = mat3(_prmMtxView) * tangent3;
    #endif
    }
    gl_Position = _prmMtxProj * _prmMtxView * position4;
}

//------------------------------------------------------------------------------
// EOF
