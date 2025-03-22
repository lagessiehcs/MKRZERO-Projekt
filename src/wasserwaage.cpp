#include <wasserwaage.hpp>

static Vector3D vector(0, 0, 0);
static int mode = WASSERWAAGE_INTENSITY_MODE;

static void changeMode();

void Wasserwaage_Init()
{
    RGB_LED_Config();
    Accelerometer_Config();
    Button_Config();
}

void Wasserwaage_Run()
{
    changeMode();

    lis.read();
    double accx = abs(lis.x * ACC_CALIBRATION);
    double accy = abs(lis.y * ACC_CALIBRATION);
    double accz = abs(lis.z * ACC_CALIBRATION);

    vector.get(accx, accy, accz);

    if (mode == WASSERWAAGE_INTENSITY_MODE)
    {
        int I = 20 * exp(-5 * (vector.angleWithZ() / 90));
        pixels.setPixelColor(0, pixels.Color(I, I, I));
    }
    else if (mode == WASSERWAAGE_COLOR_MODE)
    {
        int R = 20 * (1 - exp(-5 * (vector.angleWithX() / 90)));
        int G = 20 * (1 - exp(-5 * (vector.angleWithY() / 90)));
        int B = 20 * exp(-5 * (vector.angleWithZ() / 90));
        pixels.setPixelColor(0, pixels.Color(R, G, B));
    }

    pixels.show();
}

void Wasserwaage_Reset()
{
    pixels.clear();
    pixels.show();
}

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector3D::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3D::angleWithX() const
{
    return std::acos(x / magnitude()) * RAD_TO_DEG;
}

double Vector3D::angleWithY() const
{
    return std::acos(y / magnitude()) * RAD_TO_DEG;
}
double Vector3D::angleWithZ() const
{
    return std::acos(z / magnitude()) * RAD_TO_DEG;
}

void Vector3D::get(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

static void changeMode()
{
    button.update();

    if (button.pressed())
    {
        mode = (mode + 1) % WASSERWAAGE_NMODE;
    }
}