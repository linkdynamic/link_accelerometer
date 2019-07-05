const char homePageHtml[] PROGMEM = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>Link Accelerometer</title>
    <script src="https://code.jquery.com/jquery-3.2.1.min.js" integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4=" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
    <style type='text/css'>
     html,body{width:100%;height:100%;margin:0px;font-family:Arial;font-size:14px}.page_header{position:absolute;top:25px;width:360px;height:25px;color:rgb(108, 112, 115);text-align:left;left:15px;font-size:24px;font-weight:600}.header_div{position:absolute;top:0px;left:0px;width:100%;height:72px;background-color:black}.content_div{position:absolute;top:90px;left:15px;width:100%;height:auto}.info{margin-top:20px}.info > div{margin-top:10px;font-size:14px;font-weight:bold}.tab_div{margin:10px}form div{margin-top:5px}div.funct-group{margin-top:15px}#save-btn,#save-device-btn{margin-top:15px}.st{margin-top:10px}.st div{margin-top:10px}.st button{margin-top:10px}
    </style>
    <script>
        function getMessage(type, message) {
            var str = "<div class='alert alert-" + type + " alert-dismissable'><a href='#' class='close' data-dismiss='alert' aria-label='close'>×</a>" + "<strong>" + type.toUpperCase() + "!</strong>&nbsp;&nbsp;" + message + "</div>";
            return str;
        }
        function getData(t){$.get("/"+t,function(s){"success"==s.status&&$("#"+t+"_data").val(s.data)})}function setData(t){var s=$("#"+t+"_data").val();$.get("/set"+t+"?"+t+"data="+s,function(t){"success"==t.status?$("#msg").html(getMessage("success",t.msg)):$("#msg").html(getMessage("warning",t.msg))})}var fetchAcc=function(){$.get("/lvl",function(t){"success"==t.status&&($("#xg").val(t.data.X),$("#yg").val(t.data.Y),$("#zg").val(t.data.Z))})},disableFetchAcc=function(){$.get("/lvloff",function(t){"success"==t.status&&$("#msg").html(getMessage("success",t.msg))})},fetchHandle=null;$(document).ready(function(){getData("sr"),getData("buf"),$.get("/ip",function(t){"success"==t.status&&$("#de_ip").html(t.data)}),$.get("/d_id",function(t){"success"==t.status&&$("#de_uuid").html(t.data)}),$.get("/savedata",function(t){console.log(t),"success"==t.status&&(console.log(t),$("#uid-input").val(t.data.c_uid),$("#key-input").val(t.data.apk),$("#host-input").val(t.data.web_url),$("#secret-input").val(t.data.secret),$("#duid-input").val(t.data.dv_uid))}),$(".btn-func").on("click",function(){var t=$(this).attr("id"),s=t.replace("-btn","");$.get("/"+s,function(t){if("success"==t.status)if("logout"==s){disableFetchAcc();var c="http://"+t.data;window.location.replace(c)}else $("#msg").html(getMessage("success",t.msg))})}),$("#lvl-btn").on("click",function(){fetchHandle=setInterval(fetchAcc,5e3)}),$("#lvloff-btn").on("click",function(){disableFetchAcc(),clearInterval(fetchHandle)}),$("#save-btn").on("click",function(){var t=$("#uid-input").val(),s=$("#key-input").val(),sk=$("#secret-input").val(),h=$("#host-input").val(),c={wuid:t,wkey:s, wsec:sk, wurl:h};$.post("/conf",c,function(t){"success"==t.status&&$("#msg").html(getMessage("success",t.msg))})}),$("#save-device-btn").on("click",function(){var t=$("#duid-input").val(),s=$("#dpwd-input").val(),c={duid:t,dpwd:s};console.log(c),$.post("/dset",c,function(t){"success"==t.status&&$("#msg").html(getMessage("success",t.msg))})})});
    </script>
</head>
<body>
    <div class='header_div'>
        <div class='page_header'>Link Accelerometer</div>
    </div>
    <div class="content_div">
        <div id='msg' class='msg'></div>
        <div id="tab_div">
            <ul class="nav nav-pills">
                <li class="active"><a href="#home" data-toggle="tab">Home</a></li>
                <li><a href="#cloud" data-toggle="tab">Cloud</a></li>
                <li><a href="#setup" data-toggle="tab">Setup</a></li>
            </ul>
            <div class="tab-content clearfix">
                <div class="tab-pane active" id="home">
                    <div id='info' class='info'>
                        <div>Device IP:<span id="de_ip"></span></div>
                        <div>Device ID:<span id="de_uuid"></span></div>
                    </div><p></p>
                    <div class='content'>
                        <form method='get' action='#'>
                            <div class="input-group">
                                <span class="input-group-addon">X Axis</span>
                                <input id="xg" type="text" class="form-control" name="xg" placeholder="Acceleration">
                            </div>
                            <div class="input-group">
                                <span class="input-group-addon">Y Axis</span>
                                <input id="yg" type="text" class="form-control" name="yg" placeholder="Acceleration">
                            </div>
                            <div class="input-group">
                                <span class="input-group-addon">Z Axis</span>
                                <input id="zg" type="text" class="form-control" name="zg" placeholder="Acceleration">
                            </div>
                            <div class="funct-group">
                                <button id="lvl-btn" type="button" class="btn btn-default">Enable - Get Acceleration</button>
                                <button id="lvloff-btn" type="button" class="btn btn-default">Disable - Get Acceleration</button>
                                <button id="logout-btn" type="button" class="btn-func btn btn-default">Logout</button>
                            </div>
                        </form>
                        <div class='st'>
                            <div class='input-group'><span class='input-group-addon' id='basic-addon1'>Sample Rate</span>
                                 <input type='text' id='sr_data' name='sr_data' class='form-control' placeholder='100'>
                            </div>
                            <button type='button' class='btn  btn-default' onclick='setData("sr")'>Set Rate</button>
                            <div class='input-group'><span class='input-group-addon' id='basic-addon1'>Buffer Size</span> 
                                 <input type='text' id='buf_data' class='form-control' placeholder='10'> 
                            </div>
                            <button type='button' class='btn  btn-default' onclick='setData("buf")'>Set Buffer</button>
                        </div>
                    </div>
                </div>
                <div class="tab-pane" id="cloud">
                    <form method='post' action='#'>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="uid-input" type="text" class="form-control" placeholder="Cloud Account ID">
                                </div>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="key-input" type="text" class="form-control" placeholder="API Key">
                                </div>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="secret-input" type="text" class="form-control" placeholder="Secret Key">
                                </div>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="host-input" type="text" class="form-control" placeholder="API Web Host">
                                </div>
                            </div>
                        </div>
                        <button id="save-btn" type="button" class="btn btn-default">Save</button>
                    </form>
                </div>
                <div class="tab-pane" id="setup">
                    <form method='post' action='#'>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="duid-input" type="text" class="form-control" placeholder="Device Account ID">
                                </div>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-lg-6">
                                <div class="input-group1">
                                    <input id="dpwd-input" type="password" class="form-control" placeholder="Device Password">
                                </div>
                            </div>
                        </div>
                        <button id="save-device-btn" type="button" class="btn btn-default">Save</button>
                    </form>
                    <div class="funct-group">
                        <button id="reset-btn" type="button" class="btn-func btn btn-info">Reset Network</button>
                        <button id="reboot-btn" type="button" class="btn-func btn btn-info">Reboot</button>
                    </div>   
                </div>
            </div>
        </div>
    </div>
</body>
</html>)";
