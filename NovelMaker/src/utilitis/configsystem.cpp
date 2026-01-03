#include "configsystem.h"
#include "src/utilitis/fileutil.h"

ConfigSystem &ConfigSystem::instance()
{
    static ConfigSystem instance;
    return instance;
}

void ConfigSystem::initialize(const QString &logDir)
{


}
