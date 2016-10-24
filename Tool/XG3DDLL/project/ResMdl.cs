using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Collada141;
using System.IO;
using System.Xml;
using System.Xml.Schema;
using System.Reflection;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// xmdlファイル。
    /// </summary>
    public class ResMdl
    {
        //------------------------------------------------------------
        /// <summary>
        /// ResMdlに含まれる1メッシュを表すクラス。
        /// </summary>
        public class Mesh
        {
            /// <summary>
            /// 名前。
            /// </summary>
            public readonly string Name;
            
            /// <summary>
            /// 属するサブメッシュ。
            /// </summary>
            public readonly SubMesh[] SubMeshes;
            
            //============================================================

            //------------------------------------------------------------
            internal static Mesh FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
            {
                string name = aXml.Attributes["name"].Value;
                List<SubMesh> subMeshes = new List<SubMesh>();
                foreach (XmlNode xmlNode in aXml.SelectNodes("./n:sub_mesh", aNSMgr))
                {
                    subMeshes.Add(SubMesh.FromXml(xmlNode, aNSMgr));
                }
                return new Mesh(name, subMeshes);
            }

            //============================================================
            
            internal Mesh(string aName, IEnumerable<SubMesh> aSubMeshes)
            {
                Name = aName;
                SubMeshes = aSubMeshes.ToArray();
            }

            //============================================================

            internal void WriteXml(XmlWriter aXML)
            {
                aXML.WriteStartElement("mesh");
                {
                    aXML.WriteAttributeString("name", Name);
                    foreach (var subMesh in SubMeshes)
                    {
                        subMesh.WriteXml(aXML);
                    }
                }
                aXML.WriteEndElement();
            }
        }

        //------------------------------------------------------------
        /// <summary>
        /// ResMdlに含まれる1ノードを表すクラス。
        /// </summary>
        public class Node
        {
            //============================================================

            /// <summary>
            /// 名前。
            /// </summary>
            public readonly string Name;

            /// <summary>
            /// 親ノードの名前。なければ長さ0。
            /// </summary>
            public readonly string ParentName;

            /// <summary>
            /// SRT値。
            /// </summary>
            public readonly Transform3 Transform;

            /// <summary>
            /// バインドポーズの逆転置行列。
            /// </summary>
            public readonly Matrix3x4 InvBindPoseMtx;

            //============================================================

            //------------------------------------------------------------
            internal static Node FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
            {
                string name = aXml.Attributes["name"].Value;
                string parentName = aXml.Attributes["parent_name"].Value;
                Transform3 transform = Transform3.FromXml(aXml.SelectSingleNode("./n:transform", aNSMgr), aNSMgr);
                var invBindPoseMtx = Matrix3x4.FromXml(aXml.SelectSingleNode("./n:inv_bind_pose_mtx", aNSMgr));
                return new Node(name, parentName, transform, invBindPoseMtx);
            }

            //============================================================
            internal Node(string aName, string aParentName, Transform3 aTransform, Matrix3x4 aInvBindPoseMtx)
            {
                Name = aName;
                ParentName = aParentName;
                Transform = aTransform;
                InvBindPoseMtx = aInvBindPoseMtx;
            }

            //============================================================
            internal void WriteXml(XmlWriter aXML)
            {
                aXML.WriteStartElement("node");
                {
                    aXML.WriteAttributeString("name", Name);
                    aXML.WriteAttributeString("parent_name", ParentName);
                    Transform.WriteXml(aXML, "transform");
                    InvBindPoseMtx.WriteXml(aXML, "inv_bind_pose_mtx");
                }
                aXML.WriteEndElement();
            }
        }
        
        //------------------------------------------------------------
        /// <summary>
        /// ResMdlに含まれる1シェイプを表すクラス。
        /// </summary>
        public class Shape
        {
            //============================================================
            /// <summary>
            /// 入力データの種類。
            /// </summary>
            public enum InputKind
            {
                /// <summary>
                /// 位置。
                /// </summary>
                Position,

                /// <summary>
                /// 法線。
                /// </summary>
                Normal,

                /// <summary>
                /// 接線。
                /// </summary>
                Tangent,

                /// <summary>
                /// スキニング行列番号。
                /// </summary>
                SkinMtxIndex,

                /// <summary>
                /// スキニングウェイト値。
                /// </summary>
                SkinWeight,

                /// <summary>
                /// カラー0。
                /// </summary>
                Color0,

                /// <summary>
                /// カラー1。
                /// </summary>
                Color1,

                /// <summary>
                /// カラー2。
                /// </summary>
                Color2,

                /// <summary>
                /// カラー3。
                /// </summary>
                Color3,

                /// <summary>
                /// カラー4。
                /// </summary>
                Color4,

                /// <summary>
                /// カラー5。
                /// </summary>
                Color5,

                /// <summary>
                /// カラー6。
                /// </summary>
                Color6,

                /// <summary>
                /// カラー7。
                /// </summary>
                Color7,
                
                /// <summary>
                /// テクスチャ座標0。
                /// </summary>
                TexCoord0,

                /// <summary>
                /// テクスチャ座標1。
                /// </summary>
                TexCoord1,

                /// <summary>
                /// テクスチャ座標2。
                /// </summary>
                TexCoord2,

                /// <summary>
                /// テクスチャ座標3。
                /// </summary>
                TexCoord3,

                /// <summary>
                /// テクスチャ座標4。
                /// </summary>
                TexCoord4,

                /// <summary>
                /// テクスチャ座標5。
                /// </summary>
                TexCoord5,

                /// <summary>
                /// テクスチャ座標6。
                /// </summary>
                TexCoord6,

                /// <summary>
                /// テクスチャ座標7。
                /// </summary>
                TexCoord7,

                /// <summary>
                /// 終端。
                /// </summary>
                TERM,
            };

            //============================================================
            /// <summary>
            /// 入力データのデータタイプ。
            /// </summary>
            public enum InputType
            {
                /// <summary>
                /// 整数。
                /// </summary>
                Int,
                
                /// <summary>
                /// 浮動小数。
                /// </summary>
                Float,
            };

            /// <summary>
            /// シェイプの頂点入力データ。
            /// </summary>
            public class Input
            {
                /// <summary>
                /// 入力の種類。
                /// </summary>
                public readonly InputKind Kind;
                
                /// <summary>
                /// 1インデックスあたりの要素数。
                /// </summary>
                public readonly int ElemCount;
                
                /// <summary>
                /// インデックス配列。
                /// </summary>
                public readonly int[] IndexArray;
                
                /// <summary>
                /// 入力データタイプ。
                /// </summary>
                public readonly InputType Type;

                /// <summary>
                /// データ配列（整数版）。
                /// </summary>
                public readonly int[] IntArray;

                /// <summary>
                /// データ配列（浮動小数版）。
                /// </summary>
                public readonly float[] FloatArray;
                
                //============================================================

                //------------------------------------------------------------
                internal static Input FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
                {
                    InputKind kind = (InputKind)Enum.Parse(typeof(InputKind), aXml.Attributes["kind"].Value);
                    int elemCount = int.Parse(aXml.Attributes["elem_count"].Value);
                    int[] indexArray = Array.ConvertAll(aXml.SelectSingleNode("./n:index_array", aNSMgr).Attributes["values"].Value.Trim().Split(' '), (obj) => (int.Parse(obj)));
                    XmlNode elemArray = aXml.SelectSingleNode("./n:int_array", aNSMgr);
                    if (elemArray != null)
                    {// int
                        int[] intArray = Array.ConvertAll(elemArray.Attributes["values"].Value.Trim().Split(' '), (obj) => (int.Parse(obj)));
                        return new Input(kind, elemCount, indexArray, intArray);
                    }
                    else
                    {// float
                        elemArray = aXml.SelectSingleNode("./n:float_array", aNSMgr);
                        float[] floatArray = Array.ConvertAll(elemArray.Attributes["values"].Value.Trim().Split(' '), (obj) => (float.Parse(obj)));
                        return new Input(kind, elemCount, indexArray, floatArray);
                    }
                }

                //============================================================
                
                //------------------------------------------------------------
                // int配列版コンストラクタ。
                internal Input(InputKind aKind, int aElemCount, int[] aIndexArray, int[] aIntArray)
                {
                    Kind = aKind;
                    ElemCount = aElemCount;
                    IndexArray = aIndexArray;
                    Type = InputType.Int;
                    IntArray = aIntArray;
                }
                //------------------------------------------------------------
                // float配列版コンストラクタ。
                internal Input(InputKind aKind, int aElemCount, int[] aIndexArray, float[] aFloatArray)
                {
                    Kind = aKind;
                    ElemCount = aElemCount;
                    IndexArray = aIndexArray;
                    Type = InputType.Float;
                    FloatArray = aFloatArray;
                }

                //============================================================

                //------------------------------------------------------------
                internal void WriteXml(XmlWriter aXML)
                {
                    aXML.WriteStartElement("input");
                    {
                        aXML.WriteAttributeString("kind", Kind.ToString());
                        aXML.WriteAttributeString("elem_count", ElemCount.ToString());
                        aXML.WriteAttributeString("type", Type.ToString());

                        aXML.WriteStartElement("index_array");
                        {
                            aXML.WriteAttributeString("count", IndexArray.Length.ToString());
                            aXML.WriteAttributeString("values", string.Join(" ",IndexArray));
                        }
                        aXML.WriteEndElement();
                        
                        switch (Type)
                        {
                        case InputType.Int:
                            aXML.WriteStartElement("int_array");
                            aXML.WriteAttributeString("count", IntArray.Length.ToString());
                            aXML.WriteAttributeString("values", string.Join(" ", IntArray));
                            aXML.WriteEndElement();
                            break;

                        case InputType.Float:
                            aXML.WriteStartElement("float_array");
                            aXML.WriteAttributeString("count", FloatArray.Length.ToString());
                            aXML.WriteAttributeString("values", string.Join(" ", FloatArray));
                            aXML.WriteEndElement();
                            break;

                        default:
                            throw new Exception();
                        }
                    }
                    aXML.WriteEndElement();
                }
            };

            //============================================================

            /// <summary>
            /// シェイプ名。
            /// </summary>
            public readonly string Name;

            /// <summary>
            /// 頂点数。
            /// </summary>
            public readonly int VertexCount;

            /// <summary>
            /// 入力データ。
            /// </summary>
            public readonly Input[] Inputs;
            
            //============================================================

            //------------------------------------------------------------
            internal static Shape FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
            {
                string name = aXml.Attributes["name"].Value;
                int vertexCount = int.Parse(aXml.Attributes["vertex_count"].Value);
                List<Input> inputs = new List<Input>();
                foreach (XmlNode xmlNode in aXml.SelectNodes("./n:input", aNSMgr))
                {
                    inputs.Add(Input.FromXml(xmlNode, aNSMgr));
                }
                return new Shape(name, vertexCount, inputs);
            }

            //============================================================

            //------------------------------------------------------------
            internal Shape(string aName, int aVertexCount, IEnumerable<Input> aInputs)
            {
                Name = aName;
                VertexCount = aVertexCount;
                Inputs = aInputs.ToArray();
            }

            //============================================================

            //------------------------------------------------------------
            internal void WriteXml(XmlWriter aXML)
            {
                aXML.WriteStartElement("shape");
                {
                    aXML.WriteAttributeString("name", Name);
                    aXML.WriteAttributeString("vertex_count", VertexCount.ToString());
                    foreach (var input in Inputs)
                    {
                        input.WriteXml(aXML);
                    }
                }
                aXML.WriteEndElement();
            }
        }

        //------------------------------------------------------------
        /// <summary>
        /// ResMdlに含まれる1サブメッシュを表すクラス。
        /// </summary>
        public class SubMesh
        {
            /// <summary>
            /// シェイプ名。
            /// </summary>
            public readonly string ShapeName;

            /// <summary>
            /// マテリアル名。
            /// </summary>
            public readonly string MaterialName;
            
            /// <summary>
            /// シンプルメッシュの場合ぶらさがるノード名。それ以外は長さ0の文字列。
            /// </summary>
            public readonly string NodeName;
            
            //============================================================
            
            //------------------------------------------------------------
            internal static SubMesh FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
            {
                string shapeName = aXml.Attributes["shape_name"].Value;
                string materialName = aXml.Attributes["material_name"].Value;
                string nodeName = aXml.Attributes["node_name"].Value;
                return new SubMesh(shapeName, materialName, nodeName);
            }

            //============================================================

            //------------------------------------------------------------
            internal SubMesh(string aShapeName, string aMaterialName, string aNodeName)
            {
                ShapeName = aShapeName;
                MaterialName = aMaterialName;
                NodeName = aNodeName;
            }

            //============================================================

            //------------------------------------------------------------
            internal void WriteXml(XmlWriter aXML)
            {
                aXML.WriteStartElement("sub_mesh");
                {
                    aXML.WriteAttributeString("shape_name", ShapeName);
                    aXML.WriteAttributeString("material_name", MaterialName);
                    aXML.WriteAttributeString("node_name", NodeName);
                }
                aXML.WriteEndElement();
            }
        }

        //============================================================
        /// <summary>
        /// DAEファイルから作成。
        /// </summary>
        /// <param name="aDAE"></param>
        /// <param name="aVisualSceneIndex">モデルにするVisualSceneのインデックス値。</param>
        /// <returns></returns>
        static public ResMdl FromDAE(COLLADA aDAE, int aVisualSceneIndex)
        {
            return new ResMdl(aDAE, aVisualSceneIndex);
        }
        
        /// <summary>
        /// XMLファイルから作成。
        /// </summary>
        /// <returns></returns>
        static public ResMdl FromXml(XmlDocument aXML, FileInfo aFileInfo)
        {
            // 名前
            string name = aFileInfo.Name.Substring(0, aFileInfo.Name.Length - aFileInfo.Extension.Length);

            // 作成
            return new ResMdl(aXML.DocumentElement, aXML.NameTable, name);
        }

        /// <summary>
        /// XMLファイルから作成。
        /// </summary>
        /// <param name="aFilePath"></param>
        /// <returns></returns>
        static public ResMdl FromXml(string aFilePath)
        {
            // 設定作成
            XmlReaderSettings setting = new XmlReaderSettings();
            setting.ValidationType = ValidationType.Schema;
            {// スキーマ登録
                string schemaPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + @"/CrossFramework.XG3D.XMDL.xsd";
                XmlSchemaSet schemaSet = new XmlSchemaSet();
                schemaSet.Add(null, schemaPath);
                setting.Schemas = schemaSet;
            }

            // XMLロード
            FileInfo fileInfo = new FileInfo(aFilePath);
            XmlDocument xml = new XmlDocument();
            xml.Load(XmlReader.Create(fileInfo.FullName, setting));

            // 作成
            return FromXml(xml, fileInfo);
        }

        /// <summary>
        /// サブメッシュのシェーダーバリエーションを考慮したマテリアル名を取得する。
        /// </summary>
        /// <param name="aMdl">サブメッシュが所属するモデル。</param>
        /// <param name="aSubMesh">対象となるサブメッシュ。</param>
        /// <returns></returns>
        static public string SubMeshRawMaterialName(ResMdl aMdl, SubMesh aSubMesh)
        {
            // 今はnormalとcolorしか対応しない
            var shape = aMdl.Shapes.First(x => x.Name == aSubMesh.ShapeName);
            bool hasNormal = shape.Inputs.FirstOrDefault(x => x.Kind == Shape.InputKind.Normal) != null;
            bool hasColor = shape.Inputs.FirstOrDefault(x => x.Kind == Shape.InputKind.Color0) != null;
            return String.Format("{0}__{1}{2}", aSubMesh.MaterialName, hasNormal ? "n" : "", hasColor ? "c" : "");
        }

        //============================================================

        /// <summary>
        /// メジャーバージョン番号。
        /// </summary>
        public const byte VersionMajor = 0;

        /// <summary>
        /// マイナーバージョン番号。
        /// </summary>
        public const byte VersionMinor = 0;

        /// <summary>
        /// スキニングのインフルエンス数。
        /// </summary>
        public const int SkinInfluenceCount = 4;

        //============================================================
        /// <summary>
        /// 名前。
        /// </summary>
        public readonly string Name;

        /// <summary>
        /// ノード。
        /// </summary>
        public readonly Node[] Nodes;

        /// <summary>
        /// メッシュ。
        /// </summary>
        public readonly Mesh[] Meshes;

        /// <summary>
        /// シェイプ。
        /// </summary>
        public readonly Shape[] Shapes;

        //============================================================
        
        /// <summary>
        /// XML形式で書き出す。
        /// </summary>
        /// <param name="aFilePath"></param>
        public void WriteXml(string aFilePath)
        {
            using (MemoryStream mem = new MemoryStream())
            {
                // 設定作成
                XmlWriterSettings setting = new XmlWriterSettings();
                setting.Indent = true;
                setting.IndentChars = "    ";
                setting.NewLineChars = sNewLineChars;

                // XML作成
                using (XmlWriter xml = XmlWriter.Create(mem, setting))
                {
                    // elem
                    xml.WriteStartElement("xmdl", @"http://www.10106.net/crossframework/Schema/XG3D/XMDL");
                    {
                        // attr
                        xml.WriteAttributeString("version_major", VersionMajor.ToString());
                        xml.WriteAttributeString("version_minor", VersionMinor.ToString());

                        // elem
                        xml.WriteStartElement("body");
                        {
                            // elem
                            xml.WriteStartElement("meshes");
                            {
                                foreach (var mesh in Meshes)
                                {
                                    mesh.WriteXml(xml);
                                }
                            }
                            xml.WriteEndElement();

                            // elem
                            xml.WriteStartElement("nodes");
                            {
                                foreach (var node in Nodes)
                                {
                                    node.WriteXml(xml);
                                }
                            }
                            xml.WriteEndElement();

                            // elem
                            xml.WriteStartElement("shapes");
                            {
                                foreach (var shape in Shapes)
                                {
                                    shape.WriteXml(xml);
                                }
                            }
                            xml.WriteEndElement();
                        }
                        xml.WriteEndElement();
                    }
                    xml.WriteEndDocument();
                }

                // 書き出し
                File.WriteAllBytes(aFilePath, mem.ToArray());
            }
        }

        //============================================================

        //------------------------------------------------------------
        // メッシュ情報
        class MeshInfo
        {
            public string MeshName{ get; set; }
            public string ParentNodeName { get; set; }
            public bind_material Material { get; set; }
            public controller Controller { get; set; }
        }

        //------------------------------------------------------------
        // ShapeInputに変換するための中継クラス。
        class NormalSourceProxy
        {
            public string Id { get { return mId; } }
            public string Semantic { get { return mSemantic; } }
            public int InputIndex { get { return mInputIndex; } }
            public int ElemCount { get { return mToNewIndexTable.Length; } }

            //============================================================
            public NormalSourceProxy(source aSRC)
            {
                mId = aSRC.id;
                mInputStride = (int)aSRC.technique_common.accessor.stride;
                mOutputStride = mInputStride;
                mIsInt = (aSRC.Item as float_array) == null;
                
                if (mIsInt)
                {
                    mIntArray = ((int_array)aSRC.Item).Values;
                }
                else
                {
                    mFloatArray = ((float_array)aSRC.Item).Values;
                }

                mToNewIndexTable = new int[aSRC.technique_common.accessor.count];
            }

            //============================================================
            public void Reset(string aSemantic, Shape.InputKind aShapeInputKind, int aInputIndex)
            {
                mSemantic = aSemantic;
                mInputIndex = aInputIndex;
                mShapeInputKind = aShapeInputKind;
                mNextNewIndex = 0;
                for(int i = 0; i < mToNewIndexTable.Length; ++i)
                {
                    mToNewIndexTable[i] = -1;
                }
                mToSrcIndexList = new List<int>();
                mNewIndexList = new List<int>();
            }

            //------------------------------------------------------------
            public void NextIndex(int aIndex)
            {
                // まだ1度も使用したことのないIndexなら追加
                if (mToNewIndexTable[aIndex] == -1)
                {
                    mToNewIndexTable[aIndex] = mNextNewIndex;
                    mToSrcIndexList.Add(aIndex);
                    ++mNextNewIndex;
                }

                // リストに追加
                mNewIndexList.Add(mToNewIndexTable[aIndex]);
            }

            //------------------------------------------------------------
            public Shape.Input ToShapeInput()
            {
                // IndexArrayの再作成
                int[] newIndexArray = mNewIndexList.ToArray();
                int[] toSrcIndexArray  = mToSrcIndexList.ToArray();

                if (mIsInt)
                {
                    // IntArrayの再作成
                    List<int> newElemList = new List<int>();
                    for (int i = 0; i < toSrcIndexArray.Length; ++i)
                    {
                        int srcIndexOffset = toSrcIndexArray[i] * mInputStride;
                        for (int elemIdx = 0; elemIdx < mOutputStride; ++i)
                        {
                            int value = 0;
                            if (elemIdx < mInputStride)
                            {
                                value = mIntArray[srcIndexOffset + elemIdx];
                            }
                            newElemList.Add(value);
                        }
                    }
                    return new Shape.Input(
                        mShapeInputKind
                        , mOutputStride
                        , newIndexArray
                        , newElemList.ToArray()
                        );
                }
                else
                {
                    // FloatArrayの再作成
                    List<float> newElemList = new List<float>();
                    for (int i = 0; i < toSrcIndexArray.Length; ++i)
                    {
                        int srcIndexOffset = toSrcIndexArray[i] * mInputStride;
                        for (int elemIdx = 0; elemIdx < mOutputStride; ++elemIdx)
                        {
                            float value = 0;
                            if (elemIdx < mInputStride)
                            {
                                value = (float)mFloatArray[srcIndexOffset + elemIdx];
                            }
                            newElemList.Add(value);
                        }
                    }
                    return new Shape.Input(
                        mShapeInputKind
                        , mOutputStride
                        , newIndexArray
                        , newElemList.ToArray()
                        );
                }
            }

            //============================================================
            string mId;
            int mInputStride;
            int mOutputStride;
            bool mIsInt;
            int[] mIntArray;
            double[] mFloatArray;
            string mSemantic;
            int mInputIndex;
            Shape.InputKind mShapeInputKind;
            int mNextNewIndex;
            int[] mToNewIndexTable;
            List<int> mToSrcIndexList;
            List<int> mNewIndexList;
        };


        //------------------------------------------------------------
        // Skin用ShapeInputに変換するための中継クラス。
        class SkinSourceProxy
        {
            public string Id { get { return mId; } }
            public string Semantic { get { return mSemantic; } }
            public string[] NameArray { get { return mNameArray; } }

            //============================================================
            public SkinSourceProxy(source aSRC, int aOutputStride)
            {
                mId = aSRC.id;
                mInputStride = (int)aSRC.technique_common.accessor.stride;
                mOutputStride = aOutputStride;
                mIsInt = (aSRC.Item as float_array) == null;

                if (mIsInt)
                {
                    if (aSRC.Item is Name_array)
                    {// Name -> Index なので配列だけ作っておく
                        mNameArray = ((Name_array)aSRC.Item).Values;
                        mIntArray = new int[mNameArray.Length];
                    }
                    else
                    {// Int値そのまま
                        mIntArray = ((int_array)aSRC.Item).Values;
                    }
                }
                else
                {
                    mFloatArray = ((float_array)aSRC.Item).Values;
                }
            }

            //============================================================
            public void NameResolve(string[] aNameTable)
            {
                for (int i = 0; i < mIntArray.Length; ++i)
                {
                    mIntArray[i] = Array.IndexOf(aNameTable, mNameArray[i]);
                }
            }

            //------------------------------------------------------------
            public void Reset(string aSemantic, Shape.InputKind aShapeInputKind, int aChangedIndexArrayLength)
            {
                mSemantic = aSemantic;
                mShapeInputKind = aShapeInputKind;
                mNextNewIndex = 0;
                mToNewIndexTable = new int[aChangedIndexArrayLength];
                for (int i = 0; i < mToNewIndexTable.Length; ++i)
                {
                    mToNewIndexTable[i] = -1;
                }
                mToSrcIndexList = new List<int>();
                mNewIndexList = new List<int>();
            }

            //------------------------------------------------------------
            public void NextIndex(int aIndex)
            {
                // まだ1度も使用したことのないIndexなら追加
                if (mToNewIndexTable[aIndex] == -1)
                {
                    mToNewIndexTable[aIndex] = mNextNewIndex;
                    mToSrcIndexList.Add(aIndex);
                    ++mNextNewIndex;
                }

                // リストに追加
                mNewIndexList.Add(mToNewIndexTable[aIndex]);
            }

            //------------------------------------------------------------
            public Shape.Input ToShapeInput(int[][] aSkinBindTable)
            {
                // IndexArrayの再作成
                int[] newIndexArray = mNewIndexList.ToArray();
                int[] toSrcIndexArray = mToSrcIndexList.ToArray();

                if (mIsInt)
                {
                    // IntArrayの再作成
                    List<int> newElemList = new List<int>();
                    for (int i = 0; i < toSrcIndexArray.Length; ++i)
                    {
                        var bindIdxArray = aSkinBindTable[toSrcIndexArray[i]];
                        for (int bindIdxArrayIdx = 0; bindIdxArrayIdx < mOutputStride; ++bindIdxArrayIdx)
                        {
                            int value = 0;
                            if (bindIdxArrayIdx < bindIdxArray.Length)
                            {
                                value = mIntArray[bindIdxArray[bindIdxArrayIdx]];
                            }
                            newElemList.Add(value);
                        }
                    }
                    return new Shape.Input(
                        mShapeInputKind
                        , mOutputStride
                        , newIndexArray
                        , newElemList.ToArray()
                        );
                }
                else
                {
                    // FloatArrayの再作成
                    List<float> newElemList = new List<float>();
                    for (int i = 0; i < toSrcIndexArray.Length; ++i)
                    {
                        var bindIdxArray = aSkinBindTable[toSrcIndexArray[i]];
                        for (int bindIdxArrayIdx = 0; bindIdxArrayIdx < mOutputStride; ++bindIdxArrayIdx)
                        {
                            float value = 0;
                            if (bindIdxArrayIdx < bindIdxArray.Length)
                            {
                                value = (float)mFloatArray[bindIdxArray[bindIdxArrayIdx]];
                            }
                            newElemList.Add(value);
                        }
                    }
                    return new Shape.Input(
                        mShapeInputKind
                        , mOutputStride
                        , newIndexArray
                        , newElemList.ToArray()
                        );
                }
            }

            //============================================================
            string mId;
            int mInputStride;
            int mOutputStride;
            bool mIsInt;
            int[] mIntArray;
            double[] mFloatArray;
            string[] mNameArray;
            string mSemantic;
            Shape.InputKind mShapeInputKind;
            int mNextNewIndex;
            int[] mToNewIndexTable;
            List<int> mToSrcIndexList;
            List<int> mNewIndexList;
        };

        //============================================================
        const string sNewLineChars = "\r\n";

        //============================================================
        ResMdl(COLLADA aDAE, int aVisualSceneIndex)
        {
            // visual_scene を選択
            visual_scene vs = null;
            {
                library_visual_scenes visualScenes = (library_visual_scenes)aDAE.Items.FirstOrDefault((obj) => (obj as library_visual_scenes) != null);
                if (visualScenes == null || visualScenes.visual_scene == null)
                {
                    throw new Exception("library_visual_scenesが存在しません。");
                }
                vs = visualScenes.visual_scene[aVisualSceneIndex];
            }

            // 名前
            Name = vs.name;

            // ノード
            var nodes = new List<Node>();
            List<Pair<Node, instance_geometry>> instanceGeometries = new List<Pair<Node, instance_geometry>>();
            List<Pair<Node, instance_controller>> instanceControllers = new List<Pair<Node, instance_controller>>();
            {
                // ノード追加処理を関数化
                Action<node, node> addNode = (aNode, aParent) =>
                {
                    // Transform解析
                    Transform3 transform = new Transform3();
                    matrix mtx = (matrix)aNode.Items?.FirstOrDefault((obj) => (obj is matrix));
                    if (mtx == null)
                    {
                        // 行列のないノードは単位行列
                        transform.Rotate = Direction3.Identity.ToQuaternion();
                        transform.Scale = new Vector3(1.0f);
                    }
                    else
                    {                       
                        transform.Translate.X = (float)mtx.Values[3];
                        transform.Translate.Y = (float)mtx.Values[7];
                        transform.Translate.Z = (float)mtx.Values[11];

                        Direction3 dir3 = new Direction3();
                        dir3.Left.X = (float)mtx.Values[0];
                        dir3.Left.Y = (float)mtx.Values[4];
                        dir3.Left.Z = (float)mtx.Values[8];
                        dir3.Up.X = (float)mtx.Values[1];
                        dir3.Up.Y = (float)mtx.Values[5];
                        dir3.Up.Z = (float)mtx.Values[9];
                        dir3.Front.X = (float)mtx.Values[2];
                        dir3.Front.Y = (float)mtx.Values[6];
                        dir3.Front.Z = (float)mtx.Values[10];

                        transform.Scale.X = dir3.Left.Length();
                        transform.Scale.Y = dir3.Up.Length();
                        transform.Scale.Z = dir3.Front.Length();

                        dir3.Left = dir3.Left.Unit();
                        dir3.Up = dir3.Up.Unit();
                        dir3.Front = dir3.Front.Unit();
                        transform.Rotate = dir3.ToQuaternion();
                    }

                    // ノード追加
                    Node newNode = new Node(
                        aNode.name
                        , aParent == null ? "" : aParent.name
                        , transform
                        , Matrix3x4.Identity
                        );
                    nodes.Add(newNode);

                    // インスタンスの追加
                    if (aNode.instance_geometry != null)
                    {
                        foreach (var obj in aNode.instance_geometry)
                        {
                            instanceGeometries.Add(new Pair<Node, instance_geometry>(newNode, obj));
                        }
                    }
                    if (aNode.instance_controller != null)
                    {
                        foreach (var obj in aNode.instance_controller)
                        {
                            instanceControllers.Add(new Pair<Node, instance_controller>(newNode, obj));
                        }
                    }
                };

                // ルートノード処理
                List<node> nextNodes = new List<node>();
                foreach (node node in vs.node)
                {
                    addNode(node, null);
                    nextNodes.Add(node);
                }

                // それ以下のノード処理
                while (0 < nextNodes.Count)
                {
                    List<node> nextNextNodes = new List<node>();
                    foreach (node node in nextNodes)
                    {// 自分の子供を追加していく
                        if (node.node1 != null)
                        {
                            foreach (var childNode in node.node1)
                            {
                                addNode(childNode, node);
                                nextNextNodes.Add(childNode);
                            }
                        }
                    }
                    nextNodes = nextNextNodes;
                }
            }

            // メッシュ＆シェイプ
            var meshes = new List<Mesh>();            
            var shapes = new List<Shape>();
            do
            {
                // シェイプ名作成を関数化
                Func<geometry, int, string> generateShapeName = (aGeometry, aTriangleIndex) =>
                {
                    return aGeometry.id + "[" + aTriangleIndex.ToString() + "]";
                };

                // コントローラの取得
                library_controllers controllers = (library_controllers)aDAE.Items.FirstOrDefault((obj) => (obj as library_controllers) != null);

                // ジオメトリ取得
                library_geometries geometries = (library_geometries)aDAE.Items.FirstOrDefault((obj) => (obj as library_geometries) != null);
                if (geometries == null)
                {
                    break;
                }
                foreach (geometry geo in geometries.geometry)
                {
                    var meshInfoList = new List<MeshInfo>();
                    {
                        {// node -> geometry のパターン
                            var referencedNodes = instanceGeometries.FindAll((obj) => (obj.Second.url == "#" + geo.id));
                            foreach (var referencedNode in referencedNodes)
                            {
                                meshInfoList.Add(new MeshInfo(){
                                    MeshName = referencedNode.First.Name,
                                    ParentNodeName = referencedNode.First.Name,
                                    Material = referencedNode.Second.bind_material,
                                    });
                            }
                        }
                        if (controllers != null && controllers.controller != null)
                        {// node -> controller -> skin のパターン
                            var referencedControllers = controllers.controller.ToList().FindAll((obj) => (((skin)obj.Item).source1 == "#" + geo.id));
                            var referencedNodes = instanceControllers.FindAll((obj) => (referencedControllers.Exists((ctrl) => (obj.Second.url == "#" + ctrl.id))));
                            foreach (var referencedNode in referencedNodes)
                            {
                                meshInfoList.Add(new MeshInfo(){
                                    MeshName = referencedNode.First.Name,
                                    Material = referencedNode.Second.bind_material,
                                    Controller = controllers.controller.First(ctrl => ("#" + ctrl.id) == referencedNode.Second.url),
                                    });
                            }
                        }
                    }

                    // メッシュ化する必要がなければ何もしない
                    if (meshInfoList.Count == 0)
                    {// このモデルに属するジオメトリではないのでパス
                        continue;
                    }

                    // メッシュの準備
                    mesh mesh = geo.Item as mesh;
                    if (mesh == null)
                    {
                        continue;
                    }

                    // trianglesの配列をメモ
                    var trianglesArray = mesh.Items.ToList().FindAll((obj) => ((obj as triangles) != null));

                    // 各instance_geometry＆instance_controllerをMesh化
                    foreach (var meshEntry in meshInfoList)
                    {
                        // SubMeshを作成
                        List<SubMesh> subMeshes = new List<SubMesh>();
                        var instanceMaterials = meshEntry.Material.technique_common.ToList();
                        int trianglesIndex = 0;
                        foreach (triangles triangles in trianglesArray)
                        {
                            string shapeName = generateShapeName(geo, trianglesIndex);
                            string materialName = instanceMaterials.Find((obj) => (obj.symbol == triangles.material)).target.Substring(1);
                            subMeshes.Add(new SubMesh(shapeName, materialName, meshEntry.ParentNodeName));
                            ++trianglesIndex;
                        }

                        // メッシュを作成
                        meshes.Add(new Mesh(
                            meshEntry.MeshName
                            , subMeshes
                            ));
                    }

                    // シェイプを出力
                    {
                        // Sourceの準備
                        var sourceProxies = new List<NormalSourceProxy>();
                        var skinSourceProxies = new List<SkinSourceProxy>();
                        skin skinning = null;
                        foreach (source source in mesh.source)
                        {
                            sourceProxies.Add(new NormalSourceProxy(source));
                        }
                        foreach (var meshInfo in meshInfoList)
                        {
                            if (meshInfo.Controller != null && meshInfo.Controller.Item is skin)
                            {
                                if (skinning != null)
                                {
                                    // 複数のスキニングから１つのシェイプを参照しているケースはサポートしていないs
                                    throw new NotSupportedException();
                                }
                                skinning = (skin)meshInfo.Controller.Item;
                                foreach (var source in skinning.source)
                                {
                                    skinSourceProxies.Add(new SkinSourceProxy(source, SkinInfluenceCount));
                                }
                            }
                        }

                        // 各Triangleの処理
                        int trianglesIndex = 0;
                        foreach (triangles triangles in trianglesArray)
                        {
                            // 必要なソースの収集
                            NormalSourceProxy[] targetSourceProxies;
                            int vtxInputIdx = -1;
                            {
                                // 収集先を作成
                                var targetSourceProxiesList = new List<NormalSourceProxy>();

                                // 追加関数を定義
                                Action<string, NormalSourceProxy, int> addTargetSourceProxy = (aSemantic, aTargetSource, aInputIndex) =>
                                {
                                    Shape.InputKind inputKind;
                                    switch (aSemantic)
                                    {
                                        case "POSITION":
                                            inputKind = Shape.InputKind.Position;
                                            break;
                                        case "NORMAL":
                                            inputKind = Shape.InputKind.Normal;
                                            break;
                                        case "COLOR":
                                            inputKind = (Shape.InputKind)Enum.Parse(typeof(Shape.InputKind), "Color" + targetSourceProxiesList.Count((obj) => (obj.Semantic == "COLOR")));
                                            break;
                                        case "TEXCOORD":
                                            inputKind = (Shape.InputKind)Enum.Parse(typeof(Shape.InputKind), "TexCoord" + targetSourceProxiesList.Count((obj) => (obj.Semantic == "TEXCOORD")));
                                            break;
                                        default:
                                            throw new Exception("Unsupported semantic '" + aSemantic + "'.");
                                    }

                                    aTargetSource.Reset(aSemantic, inputKind, aInputIndex);
                                    targetSourceProxiesList.Add(aTargetSource);
                                };

                                // 追加していく
                                int inputIdx = 0;
                                foreach (InputLocalOffset input in triangles.input)
                                {
                                    string semantic = input.semantic;
                                    NormalSourceProxy targetSource = null;
                                    if (semantic == "VERTEX")
                                    {
                                        // VERTEXは複数の要素を抱えていることがあるので１つずつ追加していく
                                        foreach (var inputLocal in mesh.vertices.input)
                                        {
                                            targetSource = sourceProxies.Find((obj) => (inputLocal.source == "#" + obj.Id));
                                            addTargetSourceProxy(inputLocal.semantic, targetSource, inputIdx);
                                        }
                                        vtxInputIdx = inputIdx;
                                    }
                                    else
                                    {
                                        targetSource = sourceProxies.Find((obj) => (input.source == "#" + obj.Id));
                                        addTargetSourceProxy(semantic, targetSource, inputIdx);
                                    }
                                    ++inputIdx;
                                }

                                // 配列に変換して終了
                                targetSourceProxies = targetSourceProxiesList.ToArray();
                            }



                            // Skin対応
                            IDictionary<Shape.InputKind, SkinSourceProxy> skinSouceProxies = null;
                            IDictionary<Shape.InputKind, int[][]> skinBindTables = null;
                            if (skinning != null)
                            {
                                // Input収集
                                var offsetTable = new Dictionary<Shape.InputKind, int>();
                                {
                                    var skinSourceProxiesDic = new Dictionary<Shape.InputKind, SkinSourceProxy>();
                                    foreach (var inputLocal in skinning.vertex_weights.input)
                                    {
                                        var targetSource = skinSourceProxies.First(obj => inputLocal.source == "#" + obj.Id);
                                        Shape.InputKind inputKind;
                                        if (inputLocal.semantic == "JOINT")
                                        {
                                            targetSource.NameResolve(nodes.Select(x => { return x.Name; }).ToArray());
                                            inputKind = Shape.InputKind.SkinMtxIndex;
                                        }
                                        else if (inputLocal.semantic == "WEIGHT")
                                        {
                                            inputKind = Shape.InputKind.SkinWeight;
                                        }
                                        else
                                        {
                                            throw new NotSupportedException();
                                        }
                                        targetSource.Reset(inputLocal.semantic, inputKind, targetSourceProxies.First(x => x.Semantic == "POSITION").ElemCount);
                                        skinSourceProxiesDic.Add(inputKind, targetSource);
                                        offsetTable.Add(inputKind, (int)inputLocal.offset);
                                    }
                                    skinSouceProxies = skinSourceProxiesDic;
                                }

                                // スキンバインドテーブル作成
                                {
                                    // 格納先を用意
                                    var skinBindTableListDic = new Dictionary<Shape.InputKind, List<int[]>>();
                                    foreach (var entry in skinSouceProxies)
                                    {
                                        skinBindTableListDic.Add(entry.Key, new List<int[]>());
                                    }

                                    // 参照データの作成
                                    int[] vcountTable = skinning.vertex_weights.vcount.Split(' ').Select(x => int.Parse(x)).ToArray();
                                    int[] elemIdxTable = skinning.vertex_weights.v.Split(' ').Select(x => int.Parse(x)).ToArray();

                                    // ElemIdx配列に変換していく
                                    int elemIdxOffset = 0;
                                    for (int vcountIdx = 0; vcountIdx < vcountTable.Length; ++vcountIdx)
                                    {
                                        int vcount = vcountTable[vcountIdx];
                                        foreach (var entry in skinBindTableListDic)
                                        {
                                            var idxList = new List<int>();
                                            for (int i = 0; i < vcount; ++i)
                                            {
                                                idxList.Add(elemIdxTable[elemIdxOffset + i * skinning.vertex_weights.input.Length + offsetTable[entry.Key]]);
                                            }
                                            entry.Value.Add(idxList.ToArray());
                                        }
                                        elemIdxOffset += vcount * skinning.vertex_weights.input.Length;
                                    }

                                    // 結果をリストから配列に変換して終了s
                                    var skinBindTableDic = new Dictionary<Shape.InputKind, int[][]>();
                                    foreach (var entry in skinBindTableListDic)
                                    {
                                        skinBindTableDic.Add(entry.Key, entry.Value.ToArray());
                                    }
                                    skinBindTables = skinBindTableDic;
                                }

                                // バインドポーズ変換行列対応
                                {
                                    // floatの行列に変換
                                    var sourceInvBindMtx = skinning.source.First(src => ("#" + src.id) == skinning.joints.input.First(x => x.semantic == "INV_BIND_MATRIX").source);
                                    var invBindMtxArray = ((float_array)sourceInvBindMtx.Item).Values;

                                    // 各ノードに代入
                                    var nameArray = skinSouceProxies[Shape.InputKind.SkinMtxIndex].NameArray;
                                    for (int i = 0; i < nameArray.Length; ++i)
                                    {
                                        int offset = i * 16;
                                        int nodeIdx = nodes.FindIndex(x => x.Name == nameArray[i]);
                                        Matrix3x4 mtx = new Matrix3x4();
                                        mtx.Values[0] = (float)invBindMtxArray[offset + 0];
                                        mtx.Values[1] = (float)invBindMtxArray[offset + 4];
                                        mtx.Values[2] = (float)invBindMtxArray[offset + 8];
                                        mtx.Values[3] = (float)invBindMtxArray[offset + 1];
                                        mtx.Values[4] = (float)invBindMtxArray[offset + 5];
                                        mtx.Values[5] = (float)invBindMtxArray[offset + 9];
                                        mtx.Values[6] = (float)invBindMtxArray[offset + 2];
                                        mtx.Values[7] = (float)invBindMtxArray[offset + 6];
                                        mtx.Values[8] = (float)invBindMtxArray[offset + 10];
                                        mtx.Values[9] = (float)invBindMtxArray[offset + 3];
                                        mtx.Values[10] = (float)invBindMtxArray[offset + 7];
                                        mtx.Values[11] = (float)invBindMtxArray[offset + 11];

                                        var node = nodes[i];
                                        nodes[i] = new Node(node.Name, node.ParentName, node.Transform, mtx);
                                    }
                                }
                            }

                            // indexリストを作成
                            int[] vertxAttrIdxArray = Array.ConvertAll<string,int>(triangles.p.Trim().Split(' '), (obj) => (int.Parse(obj))); // todo: 整形されていないXMLだとこれはアウト
                            int vertexCount = (int)triangles.count * 3;
                            for (int vertexIdx = 0; vertexIdx < vertexCount; ++vertexIdx)
                            {
                                int inputIdxOffset = vertexIdx * triangles.input.Length; ;
                                for (int inputIdx = 0; inputIdx < targetSourceProxies.Length; ++inputIdx)
                                {
                                    var source = targetSourceProxies[inputIdx];
                                    int vertexAttrElemIdx = vertxAttrIdxArray[inputIdxOffset + source.InputIndex];
                                    source.NextIndex(vertexAttrElemIdx);
                                    if (skinning != null && inputIdx == vtxInputIdx)
                                    {
                                        foreach (var skinSource in skinSouceProxies)
                                        {
                                            skinSource.Value.NextIndex(vertexAttrElemIdx);
                                        }
                                    }
                                }
                            }

                            // ShapeInputに変換
                            var shapeInputs = new List<Shape.Input>();
                            foreach (var targetSourceProxy in targetSourceProxies)
                            {
                                shapeInputs.Add(targetSourceProxy.ToShapeInput());
                            }
                            if (skinning != null)
                            {
                                foreach (var targetSourceProxy in skinSouceProxies)
                                {
                                    shapeInputs.Add(targetSourceProxy.Value.ToShapeInput(skinBindTables[targetSourceProxy.Key]));
                                }
                            }

                            // Shape作成
                            string shapeName = generateShapeName(geo, trianglesIndex);
                            shapes.Add(new Shape(shapeName, vertexCount, shapeInputs));
                            ++trianglesIndex;
                        }
                    }
                }
            } while (false);

            // 結果を格納
            Nodes = nodes.ToArray();
            Meshes = meshes.ToArray();
            Shapes = shapes.ToArray();
        }        

        //------------------------------------------------------------
        ResMdl(XmlNode aXml,XmlNameTable aNameTable, string aName)
        {
            // NameTableセットアップ
            XmlNamespaceManager nsMgr = new XmlNamespaceManager(aNameTable);
            nsMgr.AddNamespace("n", aXml.NamespaceURI); // n: に割り当て。

            // 取得
            XmlNode xnBody = aXml.SelectSingleNode("./n:body", nsMgr);
            Name = aName;

            // メッシュ
            {
                List<Mesh> meshes = new List<Mesh>();
                XmlNode xnMeshes = xnBody.SelectSingleNode("./n:meshes", nsMgr);
                foreach (XmlNode xnMesh in xnMeshes)
                {
                    meshes.Add(Mesh.FromXml(xnMesh, nsMgr));
                }
                Meshes = meshes.ToArray();
            }

            // ノード
            {
                List<Node> nodes = new List<Node>();
                XmlNode xnNodes = xnBody.SelectSingleNode("./n:nodes", nsMgr);
                foreach (XmlNode xnNode in xnNodes)
                {
                    nodes.Add(Node.FromXml(xnNode, nsMgr));
                }
                Nodes = nodes.ToArray();
            }

            // シェイプ
            {
                List<Shape> shapes = new List<Shape>();
                XmlNode xnShapes = xnBody.SelectSingleNode("./n:shapes", nsMgr);
                foreach (XmlNode xnShape in xnShapes)
                {
                    shapes.Add(Shape.FromXml(xnShape, nsMgr));
                }
                Shapes = shapes.ToArray();
            }
        }
    }
}
