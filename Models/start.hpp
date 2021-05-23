#ifndef START_HPP
#define START_HPP

#include <QString>

/**
 * @brief The Difficulty enum
 */
enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

/**
 * @brief The Start class
 */
class Start
{
private:
    QString _name;
    Difficulty _difficulty;

public:
    Start();
    Start(const QString &name, Difficulty difficulty);
    Start(const Start &s);
    ~Start();
    void operator=(const Start &s);

    QString getName() const;
    void setName(const QString &name);
    void setDifficulty(Difficulty difficulty);
    Difficulty getDifficulty() const;
};

#endif // START_HPP
