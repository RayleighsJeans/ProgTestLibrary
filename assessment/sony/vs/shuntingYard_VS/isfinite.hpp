#ifdef  _WIN32
namespace std
{
    bool isfinite(double arg)
    {
        return ((arg == arg) &&
            (arg != std::numeric_limits<double>::infinity()) &&
            (arg != -std::numeric_limits<double>::infinity()));
    }
}
#endif //  __windows__