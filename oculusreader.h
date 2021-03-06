#ifndef OCULUSREADER_H
#define OCULUSREADER_H
#include <OVR.h>
#include <QObject>
#include <QTimer>
#include <QGLCamera>
#include <QVector3D>

using namespace OVR;

class OculusReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double phi READ phi WRITE setPhi NOTIFY phiChanged)
    Q_PROPERTY(double theta READ theta WRITE setTheta NOTIFY thetaChanged)
    Q_PROPERTY(double psi READ psi WRITE setPsi NOTIFY psiChanged)
    Q_PROPERTY(QGLCamera* camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    OculusReader();
    virtual ~OculusReader() { }
    Ptr<DeviceManager> pManager;
    Ptr<SensorDevice>  pSensor;
    Ptr<SensorDevice>  pSensor2;
    SensorFusion       SFusion;
    SensorFusion       SFusion2;
    double phi() const
    {
        return m_phi;
    }
    double theta() const
    {
        return m_theta;
    }

    double psi() const
    {
        return m_psi;
    }

    QGLCamera* camera() const
    {
        return m_camera;
    }

    bool enabled() const
    {
        return m_enabled;
    }

public slots:
    void setPhi(double arg)
    {
        if (m_phi != arg) {
            m_phi = arg;
            emit phiChanged(arg);
        }
    }
    void setTheta(double arg)
    {
        if (m_theta != arg) {
            m_theta = arg;
            emit thetaChanged(arg);
        }
    }

    void setPsi(double arg)
    {
        if (m_psi != arg) {
            m_psi = arg;
            emit psiChanged(arg);
        }
    }

    void readSensors();
    void setCamera(QGLCamera* arg)
    {
        if (m_camera != arg) {
            m_camera = arg;
            emit cameraChanged(arg);
        }
    }

    void setEnabled(bool arg)
    {
        if (m_enabled != arg) {
            m_isFirst = true;
            m_enabled = arg;
            emit enabledChanged(arg);
        }
    }

signals:
    void phiChanged(double arg);
    void thetaChanged(double arg);
    void psiChanged(double arg);
    void cameraChanged(QGLCamera* arg);
    void enabledChanged(bool arg);

private:
    double m_phi;
    double m_theta;
    double m_psi;
    Quatf  m_oldOrientation;
    bool   m_isFirst;
    QTimer m_timer;
    QVector3D m_upVectorStart;
    QVector3D m_viewVectorStart;
    bool m_enabled;

    QGLCamera* m_camera;
};
#endif //OCULUSREADER_H
