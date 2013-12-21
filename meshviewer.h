#ifndef MESHVIEWER_H
#define MESHVIEWER_H

#include <memory>

#include <QObject>
#include <QMatrix4x4>
#include <QPoint>
#include "openglwidget.h"
#include "OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class QWindow;
class QOpenGLShaderProgram;

class MeshViewer : public OpenGlWidget
{
    Q_OBJECT
public:
    explicit MeshViewer(QWindow *parent = 0);

    void setMesh(std::weak_ptr<Mesh> mesh);

    virtual void initialize() override;
    virtual void render() override;
signals:

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void wheelEvent(QWheelEvent *ev) override;

private:
    QOpenGLShaderProgram *m_program;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QMatrix4x4 m_pos;
    QPoint m_mousePos;

    std::weak_ptr<Mesh> m_meshptr;

};

#endif // MESHVIEWER_H
