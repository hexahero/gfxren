#include "filesystem.h"

namespace GFXREN {

namespace UTIL {

	std::string get_file_extension(const std::string& path) {

        std::string extension;

        for (size_t i = path.size(); i != 0; --i) {

            if (path[i] == '.') break;

            extension.push_back(path[i]);

        }

        std::reverse(extension.begin(), extension.end());

        return extension.c_str();
	}
    
    std::string get_file_name(const std::string& path) {

        std::string fileName;

        for (size_t i = path.size(); i != 0; --i) {

            if (path[i] == '/' || path[i] == '\\') break;

            fileName.push_back(path[i]);

        }

        std::reverse(fileName.begin(), fileName.end());

        return fileName.c_str();
    }

    std::string get_relative_path(const std::string& targetDirectory) {

        char buff[MAX_PATH];
        GetModuleFileNameA(NULL, buff, MAX_PATH);

        std::string path = buff;
        size_t targetPos = path.find(targetDirectory);

        if (targetPos != std::string::npos) {

            while (path.size() != targetPos + targetDirectory.size() + 1)
                path.pop_back();

        } 
        else {

            PRINT_ERROR(("NO TARGET \"" + targetDirectory + "\" FOUND IN PATH \"" + path + "\"").c_str(), false, false);
            
            return "INVALID PATH";
        }

        return normalize_file_path(path);
    }

    std::string get_file_via_dialog(GLFWwindow* parentWindowHandle) {

        OPENFILENAME fileDialog;
        char fileNameBuff[260];

        ZeroMemory(&fileDialog, sizeof(fileDialog));

        fileDialog.hwndOwner = glfwGetWin32Window(parentWindowHandle);
        fileDialog.lStructSize = sizeof(fileDialog);
        
        fileDialog.lpstrFile = fileNameBuff;
        fileDialog.lpstrFile[0] = '\0';
        fileDialog.nMaxFile = sizeof(fileNameBuff);

        fileDialog.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
        fileDialog.nFilterIndex = 1;

        fileDialog.lpstrFileTitle = NULL;
        fileDialog.nMaxFileTitle = 0;

        fileDialog.lpstrInitialDir = NULL;

        fileDialog.Flags = 
            OFN_PATHMUSTEXIST   | 
            OFN_FILEMUSTEXIST   | 
            OFN_NOCHANGEDIR     | 
            OFN_ENABLESIZING;

        if (GetOpenFileName(&fileDialog) == TRUE)
            return fileDialog.lpstrFile;

        return std::string(GFXREN_INVALID_FILE_PATH);
    }

    std::string normalize_file_path(std::string& path) {

         for (auto& character : path)
            if (character == '\\') character = '/'; 

        return path;
    }

}

}