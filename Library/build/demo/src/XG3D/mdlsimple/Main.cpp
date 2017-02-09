// 文字コード：UTF-8
#include <ae/base/All.hpp>
#include <ae/g3d/All.hpp>

//------------------------------------------------------------------------------
int xmain(::ae::base::Application& aApp)
{
    // ディスプレイ作成
    ::ae::base::Display display = ::ae::base::Display(::ae::base::DisplayContext());

    // レンダラー作成
    ::ae::g3d::Renderer renderer(display);

    // フレームバッファのクリアカラー設定
    renderer.fbSetClearColor(::ae::base::Color4(0.5f, 0.5f, 0.5f, 0.5f));

    // リソースの準備
    const char* fileName = "";
    {// 表示したいファイルをここで指定
        //fileName = "res/VertexColorSample.bin";
        //fileName = "res/SimpleShapes.bin";
        fileName = "res/SkinningSample.bin";
    }
    ::ae::base::Vector3 modelTranslate = ::ae::base::Vector3::Zero();
    float modelScale = 1.0f;
    if (true) {
        // Human用カスタマイズ
        fileName = "res/SkinningHuman.bin";
        modelTranslate = ::ae::base::Vector3(0.0f, -30.0f, 0.0f);
        modelScale = 0.2f;
    }
    ::ae::base::AutoMemBlock resData = ae::base::ResFile::Read(fileName);
    ::ae::g3d::ResBin resBin(resData->head());
    AE_BASE_ASSERT(resBin.isValid());
    resBin.setup();

    // インスタンス化
    const int mdlIndex = 0; // 先頭のモデルをインスタンス化
    ::ae::g3d::ResMdl resMdl = resBin.mdl(mdlIndex);
    ::ae::g3d::StateMdlTransform stateTransform(resMdl);
    ::ae::g3d::StateMdlMaterial  stateMaterial(resMdl, resBin.matSet(resMdl.name())); // モデルと同じ名前のMaterialSetを使ってマテリアルをインスタンス化

    // 1回だけ行列計算
    stateTransform.updateWorldMtx();

    // ディスプレイ表示
    display.show();

    // 回転アニメ変数
    ::ae::base::FrameCounter rotateFrame(180);

    // イベントループ
    bool doExit = false;
    while (!doExit) {
        // イベントの取得
        ::ae::base::AppEvent::EnumType event = aApp.receiveEvent();

        // イベントによって分岐
        switch (event) {
            case ::ae::base::AppEvent::Quit:
                doExit = true;
                break;

            case ::ae::base::AppEvent::Update:
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
                    ::ae::base::Matrix34::Rotate(
                        ::ae::base::Degree(360.0f * rotateFrame.rateFrame()),
                        ::ae::base::Vec3::UnitY()
                        ) 
                        * ::ae::base::Matrix34::Scale(::ae::base::Vector3(modelScale))
                        * ::ae::base::Matrix34::Translate(modelTranslate)
                    );

                // フレームバッファのクリア
                renderer.fbClear();

                // Z比較ON
                renderer.fbSetDepthCompare(true);

                // 行列設定
                renderer.sdReset();
                renderer.sdSetMtxProjection(::ae::base::Matrix44::Perspective(
                    ::ae::base::Degree(10.0f), // aFOVY
                    float(display.mainScreen().width()) / float(display.mainScreen().height()),
                    0.01f, // aNear
                    200.0f // aFar
                    ));
                renderer.sdSetMtxView(::ae::base::Matrix34::LookAt(
                    ::ae::base::Vector3(0.0f, 30.0f, 50.0f),
                    ::ae::base::Vector3::Zero(),
                    ::ae::base::Vector3::UnitY()
                    ));

                // 各メッシュの描画
                for (int meshIdx = 0; meshIdx < resMdl.meshCount(); ++meshIdx) {
                    ::ae::g3d::ResMdlMesh mesh = resMdl.mesh(meshIdx);
                    for (int subMeshIdx = 0; subMeshIdx < mesh.subMeshCount(); ++subMeshIdx) {
                        ::ae::g3d::ResMdlSubMesh subMesh = mesh.subMesh(subMeshIdx);
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
