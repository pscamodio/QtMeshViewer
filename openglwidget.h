#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWindow>
#include <QOpenGLFunctions>

class QOpenGlContext;
class QWidget;

class OpenGlWidget : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGlWidget(QWindow *parent = 0);

    QWidget* container();

    virtual void render();
    virtual void initialize();

    void setAnimating(bool animating);

signals:

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);

    void exposeEvent(QExposeEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QWidget *m_container;
    QOpenGLContext *m_context;
    QAbstractOpenGLFunctions *m_functions;

    bool m_update_pending;
    bool m_animating;
};

#endif // OPENGLWIDGET_H
