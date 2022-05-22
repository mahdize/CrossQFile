#include <QGuiApplication>
#include <QQmlApplicationEngine>
#ifdef __ANDROID__
#include <jni.h>
#endif
#include <QDebug>
#include "CrossQFile.h"

bool waitForActivityResult{false};

QString selectFileUri(){
#ifdef __ANDROID__
    waitForActivityResult = true;
    QAndroidJniObject::callStaticMethod<void>("crossqfile/MainActivity", "selectFile");
    while(waitForActivityResult){
        QCoreApplication::processEvents();
    }
    return QAndroidJniObject::callStaticObjectMethod("crossqfile/MainActivity", "getSelectedUri","()Ljava/lang/String;").toString();
#else
    return "D:\\myfile.txt";
#endif
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QString uri{selectFileUri()};
#ifdef __ANDROID__
    CrossQFile file{uri,true};
#else
    CrossQFile file{uri};
#endif
    qDebug() << "File name: " << file.fileName();
    qDebug() << "File display name: " << file.displayName();
    qDebug() << "File size: " << file.size();
    qDebug() << "File exists: " << file.exists();
    if(file.open(CrossQFile::WriteOnly)){
        file.write("Hello CrossQFile!");
        file.close();
    }else{
        qDebug() << "Could not open the file";
    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
#ifdef __ANDROID__
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_crossqfile_MainActivity_stopWaiting(JNIEnv* env, jobject thisObject){

    waitForActivityResult = false;
}
#ifdef __cplusplus
}
#endif
#endif
