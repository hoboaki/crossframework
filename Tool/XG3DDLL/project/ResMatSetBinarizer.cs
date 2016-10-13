using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// ResMatSetをバイナリ化するクラス。(GL用)
    /// </summary>
    public class ResMatSetBinarizer
    {
        /// <summary>
        ///  名前。
        /// </summary>
        public readonly string Name;

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aRes"></param>
        public ResMatSetBinarizer(ResMdl aRes)
        {
            Name = aRes.Name;
            mResMdl = aRes;
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// ResMdlから最低限必要なResMatSetを作成しバイナリ化する。
        /// </summary>
        /// <param name="aBinarizer"></param>
        /// <param name="aOption"></param>
        /// <param name="aIndex"></param>
        public void Binarize(XDataConverter.Binarizer aBinarizer, BinarizeOption aOption, int aIndex)
        {
            ResMdl res = mResMdl;
            var binarizer = aBinarizer;

            // マテリアルを列挙
            string[] materialNames;
            {
                var materialNameList = new List<string>();
                foreach (var mesh in res.Meshes)
                {
                    foreach (var subMesh in mesh.SubMeshes)
                    {
                        string matName = ResMdl.SubMeshRawMaterialName(mResMdl, subMesh);
                        if (!materialNameList.Contains(matName))
                        {
                            materialNameList.Add(matName);
                        }
                    }
                }
                materialNames = materialNameList.ToArray();
            }

            // MatBinを作成
            MatBin[] mats;
            {
                var binList = new List<MatBin>();
                foreach (var matName in materialNames)
                {
                    binList.Add(new MatBin(res, matName, aOption.TargetEngine == Engine.GLES));
                }
                mats = binList.ToArray();
            }

            // ラベルの作成
            string matsLabel = "ResMatSet[" + res.Name + "].mats";

            // ラベル名作成関数
            Func<string, int, string> createLabel = (aPrefix, aIdx) =>
            {
                return aPrefix + "[" + aIdx.ToString() + "]";
            };

            // ヘッダ追加
            binarizer.Add((ushort)aIndex);
            binarizer.Add((ushort)0); // flags
            binarizer.AddStringRef(res.Name);
            binarizer.AddReference(matsLabel);

            // データ追加
            {// mats
                // ヘッダ
                binarizer.AddAlign(4);
                binarizer.AddLabel(matsLabel);
                binarizer.Add(mats.Length);
                for (int i = 0; i < mats.Length; ++i)
                {
                    binarizer.AddReference(createLabel(matsLabel, i));
                }

                // データ
                for (int matIdx = 0; matIdx < mats.Length; ++matIdx)
                {
                    MatBin mat = mats[matIdx];

                    // ラベル
                    string paramsLabel = createLabel(matsLabel, matIdx) + ".params";
                    string vtxAttrsLabel = createLabel(matsLabel, matIdx) + ".vtxAttrs";
                    string vshSrcTextLabel = createLabel(matsLabel, matIdx) + ".vshSrcText";
                    string pshSrcTextLabel = createLabel(matsLabel, matIdx) + ".pshSrcText";

                    // ヘッダ
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(matsLabel, matIdx));
                    binarizer.Add((ushort)matIdx);
                    binarizer.Add((ushort)0); // flags
                    binarizer.AddStringRef(mat.Name);
                    binarizer.AddReference(paramsLabel);
                    binarizer.AddReference(vtxAttrsLabel);
                    binarizer.AddReference(vshSrcTextLabel);
                    binarizer.AddReference(pshSrcTextLabel);

                    // データ
                    {// params
                        // ヘッダ
                        binarizer.AddAlign(4);
                        binarizer.AddLabel(paramsLabel);
                        binarizer.Add(mat.Params.Length);
                        for (int prmIdx = 0; prmIdx < mat.Params.Length; ++prmIdx)
                        {
                            binarizer.AddReference(createLabel(paramsLabel, prmIdx));
                        }

                        // データ
                        for (int prmIdx = 0; prmIdx < mat.Params.Length; ++prmIdx)
                        {
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(createLabel(paramsLabel, prmIdx));
                        }
                    }
                    {// vtxAttrs
                        // ヘッダ
                        binarizer.AddAlign(4);
                        binarizer.AddLabel(vtxAttrsLabel);
                        binarizer.Add(mat.VtxAttrs.Length);
                        for (int attrIdx = 0; attrIdx < mat.VtxAttrs.Length; ++attrIdx)
                        {
                            binarizer.AddReference(createLabel(vtxAttrsLabel, attrIdx));
                        }

                        // データ
                        for (int attrIdx = 0; attrIdx < mat.VtxAttrs.Length; ++attrIdx)
                        {
                            // ラベル
                            string symbolNameLabel = createLabel(vtxAttrsLabel, attrIdx) + ".symbolName";

                            // ヘッダ
                            VtxAttr attr = mat.VtxAttrs[attrIdx];
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(createLabel(vtxAttrsLabel, attrIdx));
                            binarizer.AddReference(symbolNameLabel);
                            binarizer.Add((int)attr.BindInputKind);

                            // データ
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(symbolNameLabel);
                            binarizer.Add(Encoding.UTF8.GetBytes(VtxAttr.ToSymbolName(attr.BindInputKind)));
                            binarizer.Add(0); // 終端
                        }
                    }
                    {// vshSrcText
                        binarizer.AddAlign(4);
                        binarizer.AddLabel(vshSrcTextLabel);
                        binarizer.Add(Encoding.UTF8.GetBytes(mat.VShSrcText));
                        binarizer.Add(0);// 終端
                    }
                    {// pshSrcText
                        binarizer.AddAlign(4);
                        binarizer.AddLabel(pshSrcTextLabel);
                        binarizer.Add(Encoding.UTF8.GetBytes(mat.PShSrcText));
                        binarizer.Add(0);// 終端
                    }
                }
            }
        }

        //============================================================
        const string UNIFORM_PROJECTION_MATRIX = "_prmMtxProj";
        const string UNIFORM_VIEW_MATRIX       = "_prmMtxView";
        const string UNIFORM_WORLD_MATRIX = "_prmMtxWorld";

        const string VARYING_NORMAL = "_pshNormal";
        const string VARYING_COLOR0 = "_pshColor0";

        //============================================================
        //------------------------------------------------------------
        class MatBin
        {
            public readonly string Name;
            public readonly Param[] Params;
            public readonly VtxAttr[] VtxAttrs;
            public readonly string VShSrcText;
            public readonly string PShSrcText;
            //============================================================
            public MatBin(ResMdl aMdl, string aMatName, bool aIsGLES)
            {
                Name = aMatName;
                Params = new Param[0];

                // シェーダー生成前のメモ
                bool hasNormal = false;
                bool hasColor = false;
                foreach (var mesh in aMdl.Meshes)
                {
                    var subMeshes = mesh.SubMeshes.Where(x => ResMdl.SubMeshRawMaterialName(aMdl, x) == aMatName);
                    foreach (var subMesh in subMeshes)
                    {
                        if (aMdl.Shapes.First(x => x.Name == subMesh.ShapeName).Inputs.FirstOrDefault(x => x.Kind == ResMdl.Shape.InputKind.Normal) != null)
                        {
                            hasNormal = true;
                        }
                        if (aMdl.Shapes.First(x => x.Name == subMesh.ShapeName).Inputs.FirstOrDefault(x => x.Kind == ResMdl.Shape.InputKind.Color0) != null)
                        {
                            hasColor = true;
                        }
                    }
                }

                {// VtxAttrs
                    // いずれかのShapeが所持する頂点属性をこのマテリアルが使用する頂点属性とする
                    List<VtxAttr> vtxAttrs = new List<VtxAttr>();
                    vtxAttrs.Add(new VtxAttr(ResMdl.Shape.InputKind.Position)); // Positionは必須
                    if (hasNormal)
                    {
                        vtxAttrs.Add(new VtxAttr(ResMdl.Shape.InputKind.Normal));
                    }
                    if (hasColor)
                    {
                        vtxAttrs.Add(new VtxAttr(ResMdl.Shape.InputKind.Color0));
                    }
                    VtxAttrs = vtxAttrs.ToArray();
                }

                // バージョンディレクティブ
                string versionHeader = "";
                if (aIsGLES)
                {
                    versionHeader = @"#version 300 es";
                }
                else
                {
                    versionHeader = @"#version 330 core";
                }

                // VShSrcText
                using (MemoryStream mem = new MemoryStream())
                {
                    // ライターの設定
                    var writer = new StreamWriter(mem);
                    writer.NewLine = "\r\n";

                    // ヘッダ
                    writer.WriteLine(versionHeader);

                    // パラメータ
                    writer.WriteLine(@"uniform mat4 "+ UNIFORM_PROJECTION_MATRIX + ";");
                    writer.WriteLine(@"uniform mat4 "+ UNIFORM_VIEW_MATRIX + ";");
                    writer.WriteLine(@"uniform mat4 "+ UNIFORM_WORLD_MATRIX + ";");
                    writer.WriteLine("in vec3 " + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Position) + ";");
                    if (hasNormal)
                    {
                        writer.WriteLine("in vec3 " + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Normal) + ";");
                        writer.WriteLine("out vec3 " + VARYING_NORMAL + ";");
                    }
                    if (hasColor)
                    {
                        writer.WriteLine("in vec4 " + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Color0) + ";");
                        writer.WriteLine("out vec4 " + VARYING_COLOR0 + ";");
                    }

                    // メイン関数
                    writer.WriteLine(@"void main()");
                    writer.WriteLine(@"{");
                    if (hasNormal)
                    {
                        writer.WriteLine(@"    " + VARYING_NORMAL + " = " + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Normal) + ";");
                    }
                    if (hasColor)
                    {
                        writer.WriteLine(@"    " + VARYING_COLOR0 + " = " + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Color0) + ";");
                    }
                    writer.WriteLine(@"    vec4 pos4 = vec4(" + VtxAttr.ToSymbolName(ResMdl.Shape.InputKind.Position) + ",1.0);");
                    writer.WriteLine(@"    gl_Position = " + UNIFORM_PROJECTION_MATRIX + " * " +  UNIFORM_VIEW_MATRIX + " * " + UNIFORM_WORLD_MATRIX + " *  pos4;");
                    writer.WriteLine(@"}");

                    // 最後に文字列に変換
                    writer.Flush();
                    VShSrcText = Encoding.UTF8.GetString(mem.ToArray());
                }
                
                // PShSrcText
                using (MemoryStream mem = new MemoryStream())
                {
                    // ライターの設定
                    var writer = new StreamWriter(mem);
                    writer.NewLine = "\r\n";

                    // ヘッダ
                    writer.WriteLine(versionHeader);
                    writer.WriteLine(@"#ifdef GL_ES");
                    writer.WriteLine(@"    precision highp float;");
                    writer.WriteLine(@"#endif");

                    // パラメータ
                    if (hasNormal)
                    {
                        writer.WriteLine(@"in vec3 " + VARYING_NORMAL + ";");
                    }
                    if (hasColor)
                    {
                        writer.WriteLine(@"in vec4 " + VARYING_COLOR0 + ";");
                    }
                    writer.WriteLine(@"out vec4 oFragColor;");

                    // メイン関数
                    writer.WriteLine(@"void main()");
                    writer.WriteLine(@"{");
                    if (hasColor)
                    {
                        writer.WriteLine(@"    oFragColor = " + VARYING_COLOR0 + ";");
                    }
                    else if (hasNormal)
                    {
                        writer.WriteLine(@"    vec4 normalColor = vec4((" + VARYING_NORMAL + ".rgb + vec3(1.0)) * 0.5, 1.0);");
                        writer.WriteLine(@"    oFragColor = normalColor;");
                    }
                    else
                    {
                        writer.WriteLine(@"    oFragColor = vec4(1.0, 1.0, 1.0, 1.0);");
                    }
                    writer.WriteLine(@"}");

                    // 最後に文字列に変換
                    writer.Flush();
                    PShSrcText = Encoding.UTF8.GetString(mem.ToArray());
                }                
            }
        };

        //------------------------------------------------------------
        class Param
        {
        };

        //------------------------------------------------------------
        class VtxAttr
        {
            static public string ToSymbolName(ResMdl.Shape.InputKind aInputKind)
            {
                switch (aInputKind)
                {
                case ResMdl.Shape.InputKind.Position: return "_attrPosition";
                case ResMdl.Shape.InputKind.Normal: return "_attrNormal";
                case ResMdl.Shape.InputKind.WeightPaletteIndex: return "_attrWeightPaletteIndex";
                case ResMdl.Shape.InputKind.Color0: return "_attrColor0";
                case ResMdl.Shape.InputKind.Color1: return "_attrColor1";
                case ResMdl.Shape.InputKind.Color2: return "_attrColor2";
                case ResMdl.Shape.InputKind.Color3: return "_attrColor3";
                case ResMdl.Shape.InputKind.Color4: return "_attrColor4";
                case ResMdl.Shape.InputKind.Color5: return "_attrColor5";
                case ResMdl.Shape.InputKind.Color6: return "_attrColor6";
                case ResMdl.Shape.InputKind.Color7: return "_attrColor7";
                case ResMdl.Shape.InputKind.TexCoord0: return "_attrTexCoord0";
                case ResMdl.Shape.InputKind.TexCoord1: return "_attrTexCoord1";
                case ResMdl.Shape.InputKind.TexCoord2: return "_attrTexCoord2";
                case ResMdl.Shape.InputKind.TexCoord3: return "_attrTexCoord3";
                case ResMdl.Shape.InputKind.TexCoord4: return "_attrTexCoord4";
                case ResMdl.Shape.InputKind.TexCoord5: return "_attrTexCoord5";
                case ResMdl.Shape.InputKind.TexCoord6: return "_attrTexCoord6";
                case ResMdl.Shape.InputKind.TexCoord7: return "_attrTexCoord7";
                default:
                    throw new Exception();
                }
            }
            //============================================================
            public readonly ResMdl.Shape.InputKind BindInputKind;
            //============================================================
            public VtxAttr(ResMdl.Shape.InputKind aBindInputKind)
            {
                BindInputKind = aBindInputKind;
            }
        };

        //============================================================       
        ResMdl mResMdl;
    }
}
