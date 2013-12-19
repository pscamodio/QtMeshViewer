#include "openglwidget.h"

#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QDebug>

OpenGlWidget::OpenGlWidget(QWindow *parent)
    : QWindow(parent)
    , m_context(0)
    , m_update_pending(false)
    , m_container(0)
{
    setSurfaceType(QSurface::OpenGLSurface);
}

QWidget* OpenGlWidget::container()
{
    if (!m_container){
        m_container = QWidget::createWindowContainer(this);
    }
    return m_container;
}

void OpenGlWidget::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGlWidget::initialize()
{
}

void OpenGlWidget::setAnimating(bool animating)
{
    m_animating = animating;
    if (m_animating)
        renderLater();
}


void OpenGlWidget::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void OpenGlWidget::renderNow()
{
    if (!isExposed())
        return;

    m_update_pending = false;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);
    if (m_animating)
        renderLater();
}

bool OpenGlWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGlWidget::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void OpenGlWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}
