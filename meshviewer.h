#ifndef MESHVIEWER_H
#define MESHVIEWER_H

#include <QObject>
#include "openglwidget.h"

class QWindow;
class QOpenGLShaderProgram;

class MeshViewer : public OpenGlWidget
{
    Q_OBJECT
public:
    explicit MeshViewer(QWindow *parent = 0);

    virtual void initialize() override;
    virtual void render() override;
signals:

public slots:

private:
    QOpenGLShaderProgram *m_program;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    int m_frame;

};

#endif // MESHVIEWER_H
