using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// 3x4行列。
    /// </summary>
    public struct Matrix3x4
    {
        /// <summary>
        /// 単位行列。
        /// </summary>
        static public Matrix3x4 Identity
        {
            get
            {
                var obj = new Matrix3x4();
                obj.Values[0] = 1;
                obj.Values[1] = 0;
                obj.Values[2] = 0;

                obj.Values[3] = 0;
                obj.Values[4] = 1;
                obj.Values[5] = 0;

                obj.Values[6] = 0;
                obj.Values[7] = 0;
                obj.Values[8] = 1;

                obj.Values[9] = 0;
                obj.Values[10] = 0;
                obj.Values[11] = 0;
                return obj;
            }
        }

        /// <summary>
        /// XMLから読み込む。
        /// </summary>
        /// <param name="aXml"></param>
        /// <returns></returns>
        public static Matrix3x4 FromXml(XmlNode aXml)
        {
            return new Matrix3x4(aXml.Attributes["values"].Value.Trim().Split(' ').Select(x => float.Parse(x)).ToArray());                
        }

        /// <summary>
        /// x[0..2] y[0..2] z[0..2] t[0..2] の順番で格納されている値。
        /// </summary>
        public float[] Values
        {
            get
            {
                if (mValues == null)
                {
                    mValues = new float[12];
                }
                return mValues;
            }
        }
        float[] mValues;

        /// <summary>
        /// 配列から作成。
        /// </summary>
        /// <param name="aValues"></param>
        public Matrix3x4(float[] aValues)
        {
            mValues = null;
            for (int i = 0; i < Values.Length; ++i)
            {
                Values[i] = aValues[i];
            }
        }

        /// <summary>
        /// XMLに書き出す。
        /// </summary>
        /// <param name="aXML"></param>
        /// <param name="aName"></param>
        public void WriteXml(XmlWriter aXML, string aName)
        {
            aXML.WriteStartElement(aName);
            {
                aXML.WriteAttributeString("values", string.Join(" ", Values));
            }
            aXML.WriteEndElement();
        }
    }
}
