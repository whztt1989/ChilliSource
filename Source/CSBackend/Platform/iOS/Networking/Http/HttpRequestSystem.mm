//
//  HttpRequestSystem.cpp
//  Chilli Source
//  Created by Scott Downie on 23/05/2011.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2011 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifdef CS_TARGETPLATFORM_IOS

#import <CSBackend/Platform/iOS/Networking/Http/HttpRequestSystem.h>

#include <CSBackend/Platform/iOS/Core/String/NSStringUtils.h>
#include <ChilliSource/Core/Base/Application.h>
#include <ChilliSource/Core/Cryptographic/HashCRC32.h>
#include <ChilliSource/Core/String/StringUtils.h>

#import <Reachability/CSReachability.h>

#import <CFNetwork/CFNetwork.h>

namespace CSBackend
{
	namespace iOS
	{
        CS_DEFINE_NAMEDTYPE(HttpRequestSystem);
        
        //------------------------------------------------------------------
        //------------------------------------------------------------------
		bool HttpRequestSystem::IsA(CSCore::InterfaceIDType in_interfaceId) const
		{
			return in_interfaceId == CSNetworking::HttpRequestSystem::InterfaceID || in_interfaceId == HttpRequestSystem::InterfaceID;
		}
        //------------------------------------------------------------------
        //------------------------------------------------------------------
        void HttpRequestSystem::SetConnectionTimeout(u32 in_timeoutSecs)
        {
            m_connectionTimeoutSecs = in_timeoutSecs;
        }
        //------------------------------------------------------------------
        //------------------------------------------------------------------
		CSNetworking::HttpRequest* HttpRequestSystem::MakeRequest(const CSNetworking::HttpRequest::Desc& in_requestDesc, const CSNetworking::HttpRequest::Delegate& in_delegate)
        {
            CS_ASSERT(in_requestDesc.m_url.empty() == false, "Cannot make an http request to a blank url");
            
            HttpRequestUPtr request(new HttpRequest(in_requestDesc, m_connectionTimeoutSecs, [=](CSNetworking::HttpRequest* in_request, CSNetworking::HttpRequest::Result in_result)
            {
                m_finishedRequests.push_back(static_cast<HttpRequest*>(in_request));
                in_delegate(in_request, in_result);
            }));
            
            auto requestRaw = request.get();
            m_requests.push_back(std::move(request));
            
            return requestRaw;
		}
        //------------------------------------------------------------------
        //------------------------------------------------------------------
		void HttpRequestSystem::CancelAllRequests()
        {
            for(auto& request : m_requests)
            {
				request->Cancel();
			}
		}
        //------------------------------------------------------------------
        //------------------------------------------------------------------
        bool HttpRequestSystem::CheckReachability() const
        {
            CSReachability* reachability = [CSReachability reachabilityForInternetConnection];
            NetworkStatus status = [reachability currentReachabilityStatus];
            
            return (status != NotReachable);
        }
        //------------------------------------------------------------------
        //------------------------------------------------------------------
		void HttpRequestSystem::OnUpdate(f32 in_timeSinceLastUpdate)
		{
            //remove any finished requests.
            for (auto& finishedRequest : m_finishedRequests)
            {
                for (auto requestIt = m_requests.begin(); requestIt != m_requests.end();)
                {
                    if (requestIt->get() == finishedRequest)
                    {
                        requestIt = m_requests.erase(requestIt);
                        break;
                    }
                    else
                    {
                        ++requestIt;
                    }
                }
            }
            
            m_finishedRequests.clear();
		}
        //------------------------------------------------------------------
        //------------------------------------------------------------------
        void HttpRequestSystem::OnDestroy()
        {
            CancelAllRequests();

            m_requests.clear();
            m_requests.shrink_to_fit();
        }
	}
}

#endif