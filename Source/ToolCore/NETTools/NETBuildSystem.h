//
// Copyright (c) 2014-2016 THUNDERBEAST GAMES LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include <Atomic/Core/Object.h>

using namespace Atomic;

namespace ToolCore
{

    EVENT(E_NETBUILDRESULT, NETBuildResult)
    {
        PARAM(P_BUILD, Build); // NETBuild*
        PARAM(P_SUCCESS, Success); // bool = success = true;
        PARAM(P_ERRORTEXT, ErrorText); // for failure, the compilation output        
    }

    enum NETBuildStatus
    {
        NETBUILD_PENDING = 0,
        NETBUILD_BUILDING,
        NETBUILD_COMPLETE        
    };

    class Subprocess;

    class NETBuild : public Object
    {
        friend class NETBuildSystem;

        OBJECT(NETBuild)
    
    public:

        NETBuild(Context* context, const String& solutionPath, const String& platform, const String& configuration);
        virtual ~NETBuild() {};

    private:
        /// .sln or .json configuration file
        String solutionPath_;
        String configuration_;
        String platform_;
        NETBuildStatus status_;
        String allArgs_;
        String output_;
        WeakPtr<Subprocess> subprocess_;
    };

    // NET Build subsystem
    class NETBuildSystem : public Object
    {
        
        OBJECT(NETBuildSystem)

    public:

        NETBuildSystem(Context* context);
        virtual ~NETBuildSystem();

        /// Build either a .sln or .json configuration file
        NETBuild* Build(const String& solutionPath, const String& platform, const String& configuration = "Release");

    private:

        void CurrentBuildError(String errorText);

        NETBuild* GetBuild(const String& solutionPath, const String& platform, const String& configuration);

        void HandleToolUpdate(StringHash eventType, VariantMap& eventData);
        void HandleSubprocessOutput(StringHash eventType, VariantMap& eventData);
        void HandleCompileProcessComplete(StringHash eventType, VariantMap& eventData);

        SharedPtr<NETBuild> curBuild_;
        List<SharedPtr<NETBuild>> builds_;

    };

}
