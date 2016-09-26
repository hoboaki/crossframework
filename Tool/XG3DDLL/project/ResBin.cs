using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// 複数のリソースをバイナリファイルに出力するためのクラス。
    /// </summary>
    public class ResBin
    {
        //============================================================
        /// <summary>
        /// メジャーバージョン番号。
        /// </summary>
        public const byte VersionMajor = 0;

        /// <summary>
        /// マイナーバージョン番号。
        /// </summary>
        public const byte VersionMinor = 2;

        //============================================================

        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public ResBin()
        {
            mMatSetList = new List<ResMatSet>();
            mMdlList = new List<ResMdl>();
            mTexList = new List<ResTex>();
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// マテリアルセットを追加。
        /// </summary>
        /// <param name="aMatSet"></param>
        public void Add(ResMatSet aMatSet)
        {
            // 既に同じ名前のものがあればダメ
            if (mMdlList.Find((obj) => (obj.Name == aMatSet.Name)) != null)
            {
                throw new Exception("Already exist xmatset named '" + aMatSet.Name + "'.");
            }
            mMatSetList.Add(aMatSet);
        }

        //------------------------------------------------------------
        /// <summary>
        /// モデルを追加。
        /// </summary>
        /// <param name="aMdl"></param>
        public void Add(ResMdl aMdl)
        {
            // 既に同じ名前のものがあればダメ
            if (mMdlList.Find((obj) => (obj.Name == aMdl.Name)) != null)
            {
                throw new Exception("Already exist xmdl named '" + aMdl.Name + "'.");
            }
            mMdlList.Add(aMdl);
        }

        //------------------------------------------------------------
        /// <summary>
        /// テクスチャを追加。
        /// </summary>
        /// <param name="aTex"></param>
        public void Add(ResTex aTex)
        {
            // 既に同じ名前のものがあればダメ
            if (mMdlList.Find((obj) => (obj.Name == aTex.Name)) != null)
            {
                throw new Exception("Already exist xtex named '" + aTex.Name + "'.");
            }
            mTexList.Add(aTex);
        }
        
        /// <summary>
        /// バイナリ化したバイト列を取得する。
        /// </summary>
        /// <param name="aOption"></param>
        /// <returns></returns>
        public byte[] ToArray(BinarizeOption aOption)
        {
            // オプション作成
            var xbinOption = new XDataConverter.Option();
            xbinOption.IsSilent = true;
            xbinOption.Encoding = aOption.Encoding;
            xbinOption.OutputEndian = aOption.Endian;

            // バイナライズ
            var binarizer = new XDataConverter.Binarizer(xbinOption);
            {
                // ラベル
                string matSetLabel = "matset";
                string mdlLabel = "mdl";
                string texLabel = "tex";

                // ヘッダ追加
                binarizer.Add(VersionMajor);
                binarizer.Add(VersionMinor);
                binarizer.Add((ushort)aOption.TargetEngine);
                binarizer.AddReference(matSetLabel);
                binarizer.AddReference(mdlLabel);
                binarizer.AddReference(texLabel);

                // マテリアルセット
                {
                    // ラベル名作成関数
                    Func<int, string> createLabel = (aIdx) =>
                    {
                        return matSetLabel + "[" + aIdx.ToString() + "]";
                    };

                    // ソート
                    List<ResMatSetBinarizer> binarizers = new List<ResMatSetBinarizer>();
                    {// モデルから作成
                        foreach (var mdl in mMdlList)
                        {
                            binarizers.Add(new ResMatSetBinarizer(mdl));
                        }
                    }
                    binarizers.Sort(delegate(ResMatSetBinarizer a, ResMatSetBinarizer b) { return a.Name.CompareTo(b.Name); });

                    // ヘッダ作成
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(matSetLabel);
                    binarizer.Add((uint)binarizers.Count);
                    for (int i = 0; i < binarizers.Count; ++i)
                    {
                        binarizer.AddReference(createLabel(i));
                    }

                    // 各リソース
                    {
                        int idx = 0;
                        foreach (var res in binarizers)
                        {
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(createLabel(idx));
                            res.Binarize(binarizer, aOption, idx);
                            ++idx;
                        }
                    }
                }

                // モデル
                {
                    // ラベル名作成関数
                    Func<int, string> createLabel = (aIdx) =>
                    {
                        return mdlLabel + "[" + aIdx.ToString() + "]";
                    };

                    // ソート
                    List<ResMdlBinarizer> binarizers = mMdlList.ConvertAll<ResMdlBinarizer>((obj) => (new ResMdlBinarizer(obj)));
                    binarizers.Sort(delegate(ResMdlBinarizer a, ResMdlBinarizer b) { return a.Name.CompareTo(b.Name); });

                    // ヘッダ作成
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(mdlLabel);
                    binarizer.Add((uint)binarizers.Count);
                    for (int i = 0; i < binarizers.Count; ++i)
                    {
                        binarizer.AddReference(createLabel(i));
                    }

                    // 各リソース
                    {
                        int idx = 0;
                        foreach (var res in binarizers)
                        {
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(createLabel(idx));
                            res.Binarize(binarizer, aOption, idx);
                            ++idx;
                        }
                    }
                }

                // テクスチャ
                {
                    // ラベル名作成関数
                    Func<int, string> createLabel = (aIdx) =>
                    {
                        return texLabel + "[" + aIdx.ToString() + "]";
                    };

                    // ソート
                    List<ResTexBinarizer> binarizers = mTexList.ConvertAll<ResTexBinarizer>((obj) => (new ResTexBinarizer(obj)));
                    binarizers.Sort(delegate(ResTexBinarizer a, ResTexBinarizer b) { return a.Name.CompareTo(b.Name); });

                    // ヘッダ作成
                    binarizer.AddAlign(4);
                    binarizer.AddLabel(texLabel);
                    binarizer.Add((uint)binarizers.Count);
                    for (int i = 0; i < binarizers.Count; ++i)
                    {
                        binarizer.AddReference(createLabel(i));
                    }

                    // 各リソース
                    {
                        int idx = 0;
                        foreach (var res in binarizers)
                        {
                            binarizer.AddAlign(4);
                            binarizer.AddLabel(createLabel(idx));
                            res.Binarize(binarizer, aOption, idx);
                            ++idx;
                        }
                    }
                }

                // 終了
                return binarizer.Finish();
            }
        }

        //============================================================
        List<ResMatSet> mMatSetList;
        List<ResMdl>    mMdlList;
        List<ResTex>    mTexList;
    }
}
