#include "meshviewer.h"

#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QMouseEvent>
#include <QVector3D>

static const char *vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

static const char *fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col; \n"
        "}\n";

MeshViewer::MeshViewer(QWindow *parent) :
    OpenGlWidget(parent),
    m_mousePos(0, 0),
    m_meshptr()
{
    m_pos.perspective(60, 4.0/3.0, 0.1, 100.0);
    m_pos.translate(0, 0, -2);
}

void MeshViewer::setMesh(std::weak_ptr<Mesh> mesh)
{
    m_meshptr = mesh;
}

void MeshViewer::initialize()
{
    glEnable(GL_DEPTH);
    glEnable(GL_BLEND);
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void MeshViewer::render()
{
    glViewport(0, 0, width(), height());

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_program->setUniformValue(m_matrixUniform, m_pos);

    auto meshptr = m_meshptr.lock();
    if (meshptr){


    } else {
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
        };

        GLfloat colors[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,

            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,

            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,

            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
        };

        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_QUADS, 0, 24);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
    m_program->release();
}

void MeshViewer::mousePressEvent(QMouseEvent * ev)
{
    if (ev->buttons() & Qt::LeftButton){
        m_mousePos = ev->pos();
    }
}

void MeshViewer::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton){
        QVector3D move (ev->pos() - m_mousePos);
        move.setY(-move.y());
        if (ev->modifiers() & Qt::CTRL){
            QVector3D center (0.0, 0.0, 1.0);
            QVector3D axis = QVector3D::crossProduct(move, center);
            //move.normalize();
            m_pos.rotate(3.0, axis);
        } else {
            m_pos.translate(-move/100.0);
        }
        m_mousePos = ev->pos();
        renderNow();
    }
}

void MeshViewer::wheelEvent(QWheelEvent *ev)
{
    if (ev->modifiers() & Qt::CTRL){
        float delta = ev->delta()/100.0;
        auto test = m_pos.mapVector(QVector3D(0.0, 0.0, 0.1));
        m_pos.translate(test*-delta);
        renderNow();
    }
}
