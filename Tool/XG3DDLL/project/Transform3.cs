using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// SRTを表す構造体。
    /// </summary>
    public struct Transform3
    {
        /// <summary>
        /// 拡大値。
        /// </summary>
        public Vector3 Scale;

        /// <summary>
        /// 回転値。
        /// </summary>
        public Quaternion Rotate;

        /// <summary>
        /// 平行移動値。
        /// </summary>
        public Vector3 Translate;

        //============================================================

        /// <summary>
        /// XMLから読み込む。
        /// </summary>
        /// <param name="aXml"></param>
        /// <param name="aNSMgr"></param>
        /// <returns></returns>
        public static Transform3 FromXml(XmlNode aXml, XmlNamespaceManager aNSMgr)
        {
            Transform3 obj;
            obj.Scale = Vector3.FromXml(aXml.SelectSingleNode("./n:scale", aNSMgr));
            obj.Rotate = Quaternion.FromXml(aXml.SelectSingleNode("./n:rotate", aNSMgr));
            obj.Translate = Vector3.FromXml(aXml.SelectSingleNode("./n:translate", aNSMgr));
            return obj;
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// XMLに書き出す。
        /// </summary>
        /// <param name="aXML"></param>
        /// <param name="aName"></param>
        public void WriteXml(XmlWriter aXML, string aName)
        {
            aXML.WriteStartElement(aName);
            {
                Scale.WriteXml(aXML, "scale");
                Rotate.WriteXml(aXML, "rotate");
                Translate.WriteXml(aXML, "translate");
            }
            aXML.WriteEndElement();
        }
    }
}
