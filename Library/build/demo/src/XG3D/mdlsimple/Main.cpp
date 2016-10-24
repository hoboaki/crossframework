// 文字コード：UTF-8
#include <XBase/XBase.hpp>
#include <XG3D/XG3D.hpp>

//------------------------------------------------------------------------------
int xmain(::XBase::Application& aApp)
{
    // ディスプレイ作成
    ::XBase::Display display = ::XBase::Display(::XBase::DisplayContext());

    // レンダラー作成
    ::XG3D::Renderer renderer(display);

    // フレームバッファのクリアカラー設定
    renderer.fbSetClearColor(::XBase::Color4(0.5f, 0.5f, 0.5f, 0.5f));

    // リソースの準備
    const char* fileName = "";
    {// 表示したいファイルをここで指定
        //fileName = "res/VertexColorSample.bin";
        //fileName = "res/SimpleShapes.bin";
        fileName = "res/SkinningSample.bin";
    }
    ::XBase::AutoMemBlock resData = XBase::ResFile::Read(fileName);
    ::XG3D::ResBin resBin(resData->head());
    XBASE_ASSERT(resBin.isValid());
    resBin.setup();

    // インスタンス化
    const int mdlIndex = 0; // 先頭のモデルをインスタンス化
    ::XG3D::ResMdl resMdl = resBin.mdl(mdlIndex);
    ::XG3D::StateMdlTransform stateTransform(resMdl);
    ::XG3D::StateMdlMaterial  stateMaterial(resMdl, resBin.matSet(resMdl.name())); // モデルと同じ名前のMaterialSetを使ってマテリアルをインスタンス化

    // 1回だけ行列計算
    stateTransform.updateWorldMtx();

    // ディスプレイ表示
    display.show();

    // 回転アニメ変数
    ::XBase::FrameCounter rotateFrame(180);

    // イベントループ
    bool doExit = false;
    while (!doExit) {
        // イベントの取得
        ::XBase::AppEvent::EnumType event = aApp.receiveEvent();

        // イベントによって分岐
        switch (event) {
            case ::XBase::AppEvent::Quit:
                doExit = true;
                break;

            case ::XBase::AppEvent::Update:
            {
                // ディスプレイが閉じてたら終了
                if (display.isClosed()) {
                    aApp.quit();
                    continue;
                }

                // アニメーションを進める
                rotateFrame.advance();
                if (rotateFrame.isEnd()) {
                    rotateFrame.reset();
                }

                // 回転行列設定
                stateTransform.updateWorldMtx(
                    ::XBase::Matrix34::Rotate(
                        ::XBase::Degree(360.0f * rotateFrame.rateFrame()),
                        ::XBase::Vec3::UnitY()
                        )
                    );

                // フレームバッファのクリア
                renderer.fbClear();

                // Z比較ON
                renderer.fbSetDepthCompare(true);

                // 行列設定
                renderer.sdReset();
                renderer.sdSetMtxProjection(::XBase::Matrix44::Perspective(
                    ::XBase::Degree(10.0f), // aFOVY
                    float(display.mainScreen().width()) / float(display.mainScreen().height()),
                    0.01f, // aNear
                    200.0f // aFar
                    ));
                renderer.sdSetMtxView(::XBase::Matrix34::LookAt(
                    ::XBase::Vector3(0.0f, 30.0f, 50.0f),
                    ::XBase::Vector3::Zero(),
                    ::XBase::Vector3::UnitY()
                    ));

                // 各メッシュの描画
                for (int meshIdx = 0; meshIdx < resMdl.meshCount(); ++meshIdx) {
                    ::XG3D::ResMdlMesh mesh = resMdl.mesh(meshIdx);
                    for (int subMeshIdx = 0; subMeshIdx < mesh.subMeshCount(); ++subMeshIdx) {
                        ::XG3D::ResMdlSubMesh subMesh = mesh.subMesh(subMeshIdx);
                        renderer.draw(subMesh, stateTransform, stateMaterial);
                    }
                }

                // 描画の完了を待つ
                renderer.waitDrawDone();

                // 転送
                renderer.copyToDisplay(display);
            }
            break;

            default:
                break;
        }
    }


    // 終了
    return 0;
}

// EOF
