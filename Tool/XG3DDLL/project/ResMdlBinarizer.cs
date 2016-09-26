using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// ResMdlをバイナリ化するクラス。(GL用)
    /// </summary>
    public class ResMdlBinarizer
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
        public ResMdlBinarizer(ResMdl aRes)
        {
            Name = aRes.Name;
            mRes = aRes;
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// バイナリ化する。
        /// </summary>
        /// <param name="aBinarizer"></param>
        /// <param name="aOption"></param>
        /// <param name="aIndex"></param>
        public void Binarize(XDataConverter.Binarizer aBinarizer, BinarizeOption aOption, int aIndex)
        {
            ResMdl res = mRes;
            var binarizer = aBinarizer;

            // 定数
            const ushort INVALID_NODE_INDEX = 0xFFFF;
            const ushort INVALID_SKINNING_TABLE_INDEX = 0xFFFF;

            // ラベルの作成
            string matRefersLabel = "ResMdl[" + res.Name + "].matRefers";
            string meshesLabel = "ResMdl[" + res.Name + "].meshes";
            string nodesLabel = "ResMdl[" + res.Name + "].nodes";
            string shapesLabel = "ResMdl[" + res.Name + "].shapes";

            // ヘッダ追加
            binarizer.Add((ushort)aIndex);
            binarizer.Add((ushort)0); // flags
            binarizer.AddStringRef(res.Name);
            binarizer.AddReference(matRefersLabel);
            binarizer.AddReference(meshesLabel);
            binarizer.AddReference(nodesLabel);
            binarizer.AddReference(shapesLabel);

            // 各種テーブルの作成
            Dictionary<string, ushort> materialNameIdxTable = new Dictionary<string, ushort>();
            Dictionary<string, ushort> nodeNameIdxTable = new Dictionary<string, ushort>();
            Dictionary<string, ushort> shapeNameIdxTable = new Dictionary<string, ushort>();
            {
                // materialNameIdx
                foreach (var mesh in res.Meshes)
                {
                    foreach (var subMesh in mesh.SubMeshes)
                    {
                        string materialName = subMesh.MaterialName;
                        if (!materialNameIdxTable.ContainsKey(materialName))
                        {
                            materialNameIdxTable.Add(materialName, (ushort)materialNameIdxTable.Count);
                        }
                    }
                }

                // nodeNameIdx
                foreach (var node in res.Nodes)
                {
                    nodeNameIdxTable.Add(node.Name, (ushort)nodeNameIdxTable.Count);
                }

                // shapeNameIdx
                foreach (var shape in res.Shapes)
                {
                    shapeNameIdxTable.Add(shape.Name, (ushort)shapeNameIdxTable.Count);
                }
            }

            // ラベル名作成関数
            Func<string, int, string> createLabel = (aPrefix, aIdx) =>
            {
                return aPrefix + "[" + aIdx.ToString() + "]";
            };

            // データ追加
            {// matRefers
                // ヘッダ
                binarizer.AddAlign(4);
                binarizer.AddLabel(matRefersLabel);
                binarizer.Add(materialNameIdxTable.Count);
                var materialNameArray = materialNameIdxTable.ToArray().OrderBy((obj1) => (obj1.Value)).ToArray();
                for (int i = 0; i < materialNameArray.Length; ++i)
                {
                    binarizer.AddReference(createLabel(matRefersLabel, i));
                }

                // データ
                for (int i = 0; i < materialNameArray.Length; ++i)
                {
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(matRefersLabel, i));
                    binarizer.Add((ushort)i);
                    binarizer.Add((ushort)0); // flags
                    binarizer.AddStringRef(materialNameArray[i].Key);
                }
            }
            {// meshes
                // ヘッダ
                binarizer.AddAlign(4);
                binarizer.AddLabel(meshesLabel);
                binarizer.Add(res.Meshes.Length);
                for (int i = 0; i < res.Meshes.Length; ++i)
                {
                    binarizer.AddReference(createLabel(meshesLabel, i));
                }

                // データ
                for (int i = 0; i < res.Meshes.Length; ++i)
                {
                    // ラベル
                    string subMeshesLabel = createLabel(meshesLabel, i) + ".subMeshes";

                    // ヘッダ
                    ResMdl.Mesh mesh = res.Meshes[i];
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(meshesLabel, i));
                    binarizer.Add((ushort)i);
                    binarizer.Add((ushort)0); // flags
                    binarizer.AddStringRef(mesh.Name);
                    binarizer.Add((ushort)mesh.SubMeshes.Length);
                    binarizer.Add((ushort)0); // padding
                    binarizer.AddReference(createLabel(subMeshesLabel, i));

                    // データ
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(subMeshesLabel, i));
                    for (int subIdx = 0; subIdx < mesh.SubMeshes.Length; ++subIdx)
                    {
                        // ヘッダ
                        ResMdl.SubMesh subMesh = mesh.SubMeshes[subIdx];
                        binarizer.Add((ushort)subIdx);
                        binarizer.Add((ushort)0); // flags
                        binarizer.Add(subMesh.NodeName.Length == 0 ? INVALID_NODE_INDEX : nodeNameIdxTable[subMesh.NodeName]); // nodeIdx
                        binarizer.Add(shapeNameIdxTable[subMesh.ShapeName]); // shapeIdx
                        binarizer.Add(materialNameIdxTable[subMesh.MaterialName]); // matReferIdx
                        binarizer.Add((ushort)0); // padding
                    }
                }
            }
            {// nodes
                // ヘッダ
                binarizer.AddAlign(4);
                binarizer.AddLabel(nodesLabel);
                binarizer.Add(res.Nodes.Length);
                for (int i = 0; i < res.Nodes.Length; ++i)
                {
                    binarizer.AddReference(createLabel(nodesLabel, i));
                }

                // データ
                for (int i = 0; i < res.Nodes.Length; ++i)
                {
                    // ヘッダ
                    ResMdl.Node node = res.Nodes[i];
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(nodesLabel, i));
                    binarizer.Add((ushort)i);
                    binarizer.Add((ushort)0); // flags
                    binarizer.AddStringRef(node.Name);
                    binarizer.Add(node.ParentName.Length == 0 ? INVALID_NODE_INDEX : nodeNameIdxTable[node.ParentName]); // parentNodeIdx
                    {// firstChildNodeIdx
                        int findIndex = Array.FindIndex(res.Nodes, (obj) => (obj.ParentName == node.Name));
                        binarizer.Add(findIndex < 0 ? INVALID_NODE_INDEX : (ushort)findIndex);
                    }
                    {// nextSiblingNodeIdx
                        int findIndex = -1;
                        if (0 < node.ParentName.Length)
                        {
                            findIndex = Array.FindIndex(res.Nodes, i + 1, (obj) => (obj.ParentName == node.ParentName));
                        }
                        binarizer.Add(findIndex < 0 ? INVALID_NODE_INDEX : (ushort)findIndex);
                    }
                    binarizer.Add((ushort)0); // padding
                    {// rtMtx
                        Direction3 dir = node.Transform.Rotate.ToDirection3();
                        binarizer.Add(dir.Left.X);
                        binarizer.Add(dir.Left.Y);
                        binarizer.Add(dir.Left.Z);
                        binarizer.Add(dir.Up.X);
                        binarizer.Add(dir.Up.Y);
                        binarizer.Add(dir.Up.Z);
                        binarizer.Add(dir.Front.X);
                        binarizer.Add(dir.Front.Y);
                        binarizer.Add(dir.Front.Z);
                        binarizer.Add(node.Transform.Translate.X);
                        binarizer.Add(node.Transform.Translate.Y);
                        binarizer.Add(node.Transform.Translate.Z);
                    }
                    {// scale
                        binarizer.Add(node.Transform.Scale.X);
                        binarizer.Add(node.Transform.Scale.Y);
                        binarizer.Add(node.Transform.Scale.Z);
                    }
                    binarizer.AddNullReference(); // bindPosMtxRef
                }
            }
            {// shapes
                // ヘッダ
                binarizer.AddAlign(4);
                binarizer.AddLabel(shapesLabel);
                binarizer.Add(res.Shapes.Length);
                for (int i = 0; i < res.Shapes.Length; ++i)
                {
                    binarizer.AddReference(createLabel(shapesLabel, i));
                }

                // データ
                for (int shapeIdx = 0; shapeIdx < res.Shapes.Length; ++shapeIdx)
                {
                    // ラベル
                    string indexArrayDataLabel = createLabel(shapesLabel, shapeIdx) + ".indexArrayData";
                    string vtxAttrDataLabel = createLabel(shapesLabel, shapeIdx) + ".vtxAttrData";
                    string vtxAttrInfosLabel = createLabel(shapesLabel, shapeIdx) + ".vtxAttrInfos";

                    // テーブル作成
                    ResMdl.Shape shape = res.Shapes[shapeIdx];
                    Dictionary<ResMdl.Shape.InputKind, ResMdl.Shape.Input> shapeInputTable = new Dictionary<ResMdl.Shape.InputKind, ResMdl.Shape.Input>();
                    foreach (var shapeInput in shape.Inputs)
                    {
                        shapeInputTable.Add(shapeInput.Kind, shapeInput);
                    }

                    // インデックス配列の生成
                    ShapeDataTypeGL indexArrayDataType = ShapeDataTypeGL.UInt32;
                    if (shape.VertexCount <= 0xFFFF)
                    {
                        indexArrayDataType = ShapeDataTypeGL.UInt16;
                    }
                    if (shape.VertexCount <= 0xFF)
                    {
                        indexArrayDataType = ShapeDataTypeGL.UInt8;
                    }
                    int[] indexArrayData = new int[shape.VertexCount];
                    ShapeInputIndexSet[] inputIndexSets;
                    unsafe
                    {
                        // index配列の作成
                        Dictionary<ShapeInputIndexSet, int> optimizedIndex = new Dictionary<ShapeInputIndexSet, int>();
                        List<ShapeInputIndexSet> sortedIndex = new List<ShapeInputIndexSet>();
                        for (int vtxIdx = 0; vtxIdx < shape.VertexCount; ++vtxIdx)
                        {
                            // キーを作成
                            ShapeInputIndexSet tmpInputIndexSet = new ShapeInputIndexSet();
                            foreach (var shapeInput in shape.Inputs)
                            {
                                tmpInputIndexSet.idx[(int)shapeInput.Kind] = shapeInput.IndexArray[vtxIdx];
                            }

                            // あるかないか
                            if (optimizedIndex.ContainsKey(tmpInputIndexSet))
                            {// 既にある
                                indexArrayData[vtxIdx] = optimizedIndex[tmpInputIndexSet];
                            }
                            else
                            {// ないので追加
                                int nextIndex = optimizedIndex.Count;
                                indexArrayData[vtxIdx] = optimizedIndex.Count;
                                optimizedIndex.Add(tmpInputIndexSet, nextIndex);
                                sortedIndex.Add(tmpInputIndexSet);
                            }
                        }
                        inputIndexSets = sortedIndex.ToArray();
                    };

                    // 頂点属性の情報だけ作成
                    int vtxAttrDataUnitSize = 0;
                    VtxAttrInfo[] vtxAttrInfos;
                    {
                        var vtxAttrInfosList = new List<VtxAttrInfo>();
                        foreach (var shapeInput in shape.Inputs)
                        {
                            // 型の選別
                            ShapeDataTypeGL dataType;
                            switch (shapeInput.Kind)
                            {
                            // todo: 最適化
                            //case Shape.InputKind.Color0:
                            //case Shape.InputKind.Color1:
                            //case Shape.InputKind.Color2:
                            //case Shape.InputKind.Color3:
                            //case Shape.InputKind.Color4:
                            //case Shape.InputKind.Color5:
                            //case Shape.InputKind.Color6:
                            //case Shape.InputKind.Color7:
                            //    {
                            //        dataType = ShapeDataTypeGL.UInt8;
                            //    }
                            //    break;
                            default:
                                {
                                    dataType = shapeInput.Type == ResMdl.Shape.InputType.Float
                                        ? ShapeDataTypeGL.Float
                                        : ShapeDataTypeGL.Int32;
                                }
                                break;
                            }

                            vtxAttrInfosList.Add(new VtxAttrInfo(
                                shapeInput.Kind
                                , dataType
                                , (byte)shapeInput.ElemCount
                                , (byte)vtxAttrDataUnitSize
                                ));
                            vtxAttrDataUnitSize += toByteSize(dataType) * shapeInput.ElemCount;
                        }
                        vtxAttrInfos = vtxAttrInfosList.ToArray();
                    }

                    // ヘッダ
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(createLabel(shapesLabel, shapeIdx));
                    binarizer.Add((ushort)shapeIdx);
                    binarizer.Add((ushort)0); // flags
                    binarizer.AddStringRef(shape.Name);
                    binarizer.Add(INVALID_SKINNING_TABLE_INDEX);
                    binarizer.Add((byte)indexArrayDataType); // indexArrayDataType
                    binarizer.Add((byte)vtxAttrInfos.Length); // vtxAttrInfoCount
                    binarizer.Add(indexArrayData.Length); // indexArrayDataCount
                    binarizer.AddReference(indexArrayDataLabel); // indexArrayDataRef
                    binarizer.AddReference(vtxAttrInfosLabel); // vtxAttrInfosRef
                    binarizer.Add(vtxAttrDataUnitSize * inputIndexSets.Length); // vtxAttrDataSize
                    binarizer.Add(vtxAttrDataUnitSize); // vtxAttrDataStride
                    binarizer.AddReference(vtxAttrDataLabel); // vtxAttrDataRef

                    // データ
                    {// indexArrayData
                        binarizer.AddAlign(4);
                        binarizer.AddLabel(indexArrayDataLabel);
                        switch (indexArrayDataType)
                        {
                        case ShapeDataTypeGL.UInt8:
                            {
                                byte[] tmp = Array.ConvertAll(indexArrayData, (val) => ((byte)val));
                                binarizer.Add(tmp);
                            }
                            break;

                        case ShapeDataTypeGL.UInt16:
                            {
                                ushort[] tmp = Array.ConvertAll(indexArrayData, (val) => ((ushort)val));
                                binarizer.Add(tmp);
                            }
                            break;

                        default:
                            binarizer.Add(indexArrayData);
                            break;
                        }
                        {// vtxAttrInfos
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(vtxAttrInfosLabel);
                            foreach (var info in vtxAttrInfos)
                            {
                                binarizer.Add((byte)info.InputKind);
                                binarizer.Add((byte)info.DataType);
                                binarizer.Add((byte)info.ElemCount);
                                binarizer.Add((byte)info.Offset);
                            }
                        }
                        {// vtxAttrData
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(vtxAttrDataLabel);

                            // BinarizeInputに変換
                            BinarizedInput[] binarizedInputs = new BinarizedInput[vtxAttrInfos.Length];
                            for (int i = 0; i < vtxAttrInfos.Length; ++i)
                            {
                                BinarizedInput binarizedInput = new BinarizedInput();
                                ResMdl.Shape.Input input = shape.Inputs[i];
                                switch (vtxAttrInfos[i].DataType)
                                {
                                case ShapeDataTypeGL.Float:
                                    if (input.Type != ResMdl.Shape.InputType.Float)
                                    {
                                        throw new Exception();
                                    }
                                    binarizedInput.Float = input.FloatArray;
                                    break;

                                case ShapeDataTypeGL.Int32:
                                    if (input.Type != ResMdl.Shape.InputType.Int)
                                    {
                                        throw new Exception();
                                    }
                                    binarizedInput.Int32 = input.IntArray;
                                    break;

                                default:
                                    throw new Exception();
                                }
                                binarizedInputs[i] = binarizedInput;
                            }

                            // データ列をはいていく
                            unsafe
                            {
                                for (int indexSetIdx = 0; indexSetIdx < inputIndexSets.Length; ++indexSetIdx)
                                {
                                    ShapeInputIndexSet indexSet = inputIndexSets[indexSetIdx];
                                    for (int inputIdx = 0; inputIdx < vtxAttrInfos.Length; ++inputIdx)
                                    {
                                        VtxAttrInfo attrInfo = vtxAttrInfos[inputIdx];
                                        BinarizedInput input = binarizedInputs[inputIdx];
                                        int elemCount = attrInfo.ElemCount;
                                        int index = indexSet.idx[(int)attrInfo.InputKind] * elemCount;
                                        switch (attrInfo.DataType)
                                        {
                                        case ShapeDataTypeGL.Float:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.Float[index + elemIdx]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.Int8:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.Int8[index+elemIdx]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.Int16:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.Int16[index+elemIdx]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.Int32:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.Int32[index+elemIdx
                                                    ]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.UInt8:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.UInt8[index + elemIdx]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.UInt16:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.UInt16[index + elemIdx]);
                                            }
                                            break;

                                        case ShapeDataTypeGL.UInt32:
                                            for (int elemIdx = 0; elemIdx < elemCount; ++elemIdx)
                                            {
                                                binarizer.Add(input.UInt32[index + elemIdx]);
                                            }
                                            break;

                                        default:
                                            throw new Exception();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //============================================================

        //------------------------------------------------------------
        enum ShapeDataTypeGL
        {
            Float,
            Int8,
            Int16,
            Int32,
            UInt8,
            UInt16,
            UInt32,
        };

        //------------------------------------------------------------
        unsafe struct ShapeInputIndexSet
        {
            public fixed int idx[(int)ResMdl.Shape.InputKind.TERM];
        };

        //------------------------------------------------------------
        class VtxAttrInfo
        {
            public readonly ResMdl.Shape.InputKind InputKind;
            public readonly ShapeDataTypeGL DataType;
            public readonly byte ElemCount;
            public readonly byte Offset;

            //============================================================
            public VtxAttrInfo(
                ResMdl.Shape.InputKind aInputKind
                , ShapeDataTypeGL aDataType
                , byte aElemCount
                , byte aOffset
                )
            {
                InputKind = aInputKind;
                DataType = aDataType;
                ElemCount = aElemCount;
                Offset = aOffset;
            }
        };

        //------------------------------------------------------------
        // バイナリ用にコンバート済みのinputデータ配列。
        class BinarizedInput
        {
            public float[] Float = null;
            public sbyte[] Int8 = null;
            public short[] Int16 = null;
            public int[] Int32 = null;
            public byte[] UInt8 = null;
            public ushort[] UInt16 = null;
            public uint[] UInt32 = null;
        };

        //============================================================

        //------------------------------------------------------------
        static int toByteSize(ShapeDataTypeGL aType)
        {
            switch (aType)
            {
            case ShapeDataTypeGL.Int8:
            case ShapeDataTypeGL.UInt8:
                return 1;

            case ShapeDataTypeGL.Int16:
            case ShapeDataTypeGL.UInt16:
                return 2;

            default:
                return 4;
            }
        }

        //============================================================
        ResMdl mRes;
    }
}
