# cooper API 接口文档（V3）
- [cooper API 接口文档（V3）](#cooper-api-%E6%8E%A5%E5%8F%A3%E6%96%87%E6%A1%A3%EF%BC%88v3%EF%BC%89)
    - [前言](#%E5%89%8D%E8%A8%80)
    - [修改记录](#%E4%BF%AE%E6%94%B9%E8%AE%B0%E5%BD%95)
    - [基础文件](#%E5%9F%BA%E7%A1%80%E6%96%87%E4%BB%B6)
        - [模型](#%E6%A8%A1%E5%9E%8B)
        - [用户权限访问接口](#%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90%E8%AE%BF%E9%97%AE%E6%8E%A5%E5%8F%A3)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal](#get-apiv3linkssidw21512stw6appeal)
                - [REQ](#req)
                - [RSP](#rsp)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report](#get-apiv3linkssidw21512stw6report)
                - [REQ](#req)
                - [RSP](#rsp)
- [cooper API 接口文档（V3）](#cooper-api-%E6%8E%A5%E5%8F%A3%E6%96%87%E6%A1%A3%EF%BC%88v3%EF%BC%89)
    - [前言](#%E5%89%8D%E8%A8%80)
    - [修改记录](#%E4%BF%AE%E6%94%B9%E8%AE%B0%E5%BD%95)
    - [基础文件](#%E5%9F%BA%E7%A1%80%E6%96%87%E4%BB%B6)
        - [模型](#%E6%A8%A1%E5%9E%8B)
        - [用户权限访问接口](#%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90%E8%AE%BF%E9%97%AE%E6%8E%A5%E5%8F%A3)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal](#get-apiv3linkssidw21512stw6appeal)
                - [REQ](#req)
                - [RSP](#rsp)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report](#get-apiv3linkssidw21512stw6report)
                - [REQ](#req)
                - [RSP](#rsp)
        [用户权限访问接口](#%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90%E8%AE%BF%E9%97%AE%E6%8E%A5%E5%8F%A3)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal](#get-apiv3linkssidw21512stw6appeal)
                - [审核不通过后，申诉](#%E5%AE%A1%E6%A0%B8%E4%B8%8D%E9%80%9A%E8%BF%87%E5%90%8E%EF%BC%8C%E7%94%B3%E8%AF%89)
                    - [REQ参数](#req%E5%8F%82%E6%95%B0)
                    - [RSP](#rsp)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report](#get-apiv3linkssidw21512stw6report)
                - [举报分享链接](#%E4%B8%BE%E6%8A%A5%E5%88%86%E4%BA%AB%E9%93%BE%E6%8E%A5)
                    - [REQ参数](#req%E5%8F%82%E6%95%B0)
                    - [RSP](#rsp)
                    - 
## 前言
该文档为cooper模块v3接口文档(待补充)
模板说明：
1. 模块之间用 `------` 分隔符分隔
2. 接口使用 `####` 标记
3. 修改记录记得增加
4. 目录研究中


 
## 修改记录
> 2018/2/28  晋永康
> - 创建文档

> 2018/3/8  王强
> - 添加文件存储、分享链接、团队、统计、星标、评论、预览相关接口

> 2018/5/11  王强
> - 添加根据fileid,linkid,recycleid获取文件及其下载信息的开发者接口，供web office调用


------
## 基础文件
### 模型
NA
### 用户权限访问接口
#### GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal
*审核不通过后申诉*
##### REQ
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  sid        | string |   true   |         |  path    |   分享链接sid       |

------

##### RSP
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  result     | string |   true   |         |  path    |   true/false       |


#### GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report
*举报分享链接*
##### REQ
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  sid        | string |   true   |         |  path    |   分享链接sid       |

------

##### RSP
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  result     | string |   true   |         |  path    |   true/false       |

# cooper API 接口文档（V3）
- [cooper API 接口文档（V3）](#cooper-api-%E6%8E%A5%E5%8F%A3%E6%96%87%E6%A1%A3%EF%BC%88v3%EF%BC%89)
    - [前言](#%E5%89%8D%E8%A8%80)
    - [修改记录](#%E4%BF%AE%E6%94%B9%E8%AE%B0%E5%BD%95)
    - [基础文件](#%E5%9F%BA%E7%A1%80%E6%96%87%E4%BB%B6)
        - [模型](#%E6%A8%A1%E5%9E%8B)
        - [用户权限访问接口](#%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90%E8%AE%BF%E9%97%AE%E6%8E%A5%E5%8F%A3)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal](#get-apiv3linkssidw21512stw6appeal)
                - [REQ](#req)
                - [RSP](#rsp)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report](#get-apiv3linkssidw21512stw6report)
                - [REQ](#req)
                - [RSP](#rsp)
        [用户权限访问接口](#%E7%94%A8%E6%88%B7%E6%9D%83%E9%99%90%E8%AE%BF%E9%97%AE%E6%8E%A5%E5%8F%A3)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal](#get-apiv3linkssidw21512stw6appeal)
                - [审核不通过后，申诉](#%E5%AE%A1%E6%A0%B8%E4%B8%8D%E9%80%9A%E8%BF%87%E5%90%8E%EF%BC%8C%E7%94%B3%E8%AF%89)
                    - [REQ参数](#req%E5%8F%82%E6%95%B0)
                    - [RSP](#rsp)
            - [GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report](#get-apiv3linkssidw21512stw6report)
                - [举报分享链接](#%E4%B8%BE%E6%8A%A5%E5%88%86%E4%BA%AB%E9%93%BE%E6%8E%A5)
                    - [REQ参数](#req%E5%8F%82%E6%95%B0)
                    - [RSP](#rsp)
                    
## 前言
该文档为cooper模块v3接口文档(待补充)
模板说明：
1. 模块之间用 `------` 分隔符分隔
2. 接口使用 `####` 标记
3. 修改记录记得增加
4. 目录研究中


 
## 修改记录
> 2018/2/28  晋永康
> - 创建文档

> 2018/3/8  王强
> - 添加文件存储、分享链接、团队、统计、星标、评论、预览相关接口

> 2018/5/11  王强
> - 添加根据fileid,linkid,recycleid获取文件及其下载信息的开发者接口，供web office调用


------
## 基础文件
### 模型
NA
### 用户权限访问接口

#### GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/appeal
*审核不通过后申诉*
##### REQ
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  sid        | string |   true   |         |  path    |   分享链接sid       |

------

##### RSP
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  result     | string |   true   |         |  path    |   true/false       |


#### GET /api/v3/links/{sid:\\w{21,512}|[st]\\w{6}}/report
*举报分享链接*
##### REQ
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  sid        | string |   true   |         |  path    |   分享链接sid       |

------

##### RSP
| param       | type   | required | default | location | description        |
|-------------|--------|----------|---------|----------|--------------------|
|  result     | string |   true   |         |  path    |   true/false       |