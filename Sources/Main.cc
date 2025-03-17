#include <stdexcept>
#include <format>
#include "EntryPoint.h"
#include "FilePathUtil.h"
#include "JavaPathUtil.h"
#include "ProcessLaunchUtil.h"
#include "Win32Exception.h"

void Main() {
    const std::wstring mindustryParentPath = FilePathUtil::GetParent(FilePathUtil::GetProgramFileName());
    const std::wstring mindustryJarPath = FilePathUtil::Combine(mindustryParentPath, L"Mindustry.jar");
    if (!FilePathUtil::Exists(mindustryJarPath)) {
        Win32Exception::ThrowLastError(ERROR_FILE_NOT_FOUND, "File 'Mindustry.jar' not found.");
    }
    const std::wstring mindustryCommand = std::format(L"-jar \"{}\"", mindustryJarPath);
    ProcessLaunchUtil::SetEnvironment(L"AppData", mindustryParentPath);
    ProcessLaunchUtil::LaunchProcess(JavaPathUtil::GetJavawPath(), mindustryCommand);
}
