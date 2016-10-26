#version auto
// 文字コード：UTF-8
//------------------------------------------------------------------------------
in vec3 _attrPosition;

// Normal
#if defined(_USE_ATTR_NORMAL)
    in vec3 _attrNormal;
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
    uniform vec4 _prmMtxBones[64 * 3];
#endif

//------------------------------------------------------------------------------
#if defined(_USE_ATTR_NORMAL)
    out vec3 pshNormal;
#endif

#if defined(_USE_ATTR_COLOR0)
    out vec4 pshColor0;
#endif

//------------------------------------------------------------------------------
void main()
{
#if defined(_USE_ATTR_NORMAL)
    pshNormal = _attrNormal;
#endif
#if defined(_USE_ATTR_COLOR0)
    pshColor0 = _attrColor0;
#endif

	// Pos
	vec4 pos4; 
#if defined(_USE_ATTR_SKIN_MTX_INDEX)
	{
		ivec4 boneIndexVec = _attrSkinMtxIndex;
		vec4 boneWeightVec = _attrSkinWeight;
		vec3 pos = vec3(0);
		for(int skinSrcIdx = 0; skinSrcIdx < 4; skinSrcIdx++) {
			// Position
			float boneWeight = boneWeightVec.x;
			int boneIndex = boneIndexVec.x;
            if (skinSrcIdx == 0) {
                boneIndex = 2;
                if (boneWeight > 0.3) {
                    //pshNormal = vec3(0,0,1);
                }
            }
            else if (skinSrcIdx == 1) {
                boneIndex = 3;
                if (boneWeight > 0.3) {
                    //pshNormal = vec3(1,0,0);
                }
            }
            else {
                boneIndex = 0;
                if (boneWeight > 0.0) {
                    pshNormal = vec3(0,1,0);
                }
            }
            int boneBaseIndex = boneIndex * 3;
			mat4x3 boneMatrix = mat4x3(
                _prmMtxBones[boneBaseIndex],
                _prmMtxBones[boneBaseIndex + 1],
                _prmMtxBones[boneBaseIndex + 2]
                );
            pos += (boneMatrix * vec4(_attrPosition, 1.0)).xyz * boneWeight;

			// Normal & Tangent
            //mat3 normalMatrix = BoneMatrixArrayIT[boneIndexVec.x];    
            //objectNormal += normalMatrix * inNormal * boneWeightVec.x;
            //objectTangent += normalMatrix * inTangent.xyz * boneWeightVec.x;

			// ローテーション
			boneIndexVec = boneIndexVec.yzwx;
			boneWeightVec = boneWeightVec.yzwx;
		}
		pos4 = vec4(pos, 1.0);
	}
#else
	pos4 = _prmMtxWorld * vec4(_attrPosition, 1.0);
#endif

    // Output
    gl_Position = _prmMtxProj * _prmMtxView * pos4;
}

//------------------------------------------------------------------------------
// EOF
