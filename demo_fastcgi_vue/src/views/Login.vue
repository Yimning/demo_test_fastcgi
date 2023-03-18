<template>

    <div class="login-wrap">
        <div class="ms-login">
            <div class="ms-title">人脸考勤管理系统</div>
            <el-form :model="param" :rules="rules" ref="login" label-width="0px" class="ms-content">
                <el-form-item prop="userID">
                    <el-input v-model="param.userID" placeholder="账号">
                        <el-button slot="prepend" icon="el-icon-lx-people"></el-button>
                    </el-input>
                </el-form-item>
                <el-form-item prop="passWord">
                    <el-input type="passWord" placeholder="密码" v-model="param.passWord" @keyup.enter.native="submitForm()">
                        <el-button slot="prepend" icon="el-icon-lx-lock"></el-button>
                    </el-input>
                </el-form-item>

                <el-form-item prop="userFlag">
                    <div class="userFlag">
                        <el-radio v-model="param.userFlag" label="0">学生</el-radio>
                        <el-radio v-model="param.userFlag" label="1">教师</el-radio>
                        <el-radio v-model="param.userFlag" label="2">管理员</el-radio>
                    </div>
                </el-form-item>

                <div class="login-btn">
                    <el-button type="primary" @click="submitForm('param')">登录</el-button>
                </div>
                <div class="login-btn">
                    <el-button type="primary" @click="resetForm('param')">重置</el-button>
                </div>

                <div class="btn-txt">
                    <el-button type="text" @click="forgetPwd">忘记密码</el-button>
                    <el-button class="btn-right" type="text" @click="faceLogin">刷脸登录</el-button>
                </div>
                <div class="login-tips">
                    <p class="text">Tips : 若无账号则联系官方管理员</p>
                </div>
            </el-form>
        </div>
        <el-dialog title="刷脸登录" :visible.sync="FaceLoginVisible" width="45%" @close="closeDialog">
            <!-- <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item>
                    <i class="el-icon-lx-redpacket_fill"></i> js调用摄像头拍照上传图片
                </el-breadcrumb-item>
            </el-breadcrumb>
            </div>-->
            <!--提示-->
            <div align="center">
                <p id="flag" ref="flag" class="tishi">{{ this.tips }}</p>
            </div>
            <div class="container">
                <div align="center">
                    <!--开启摄像头-->
                    <video id="video" ref="video" width="480px" height="400px" autoplay="autoplay"></video>
                    <!--canvas截取流-->
                    <canvas ref="canvas" id="canvas" width="480px" height="400px" style="display: none"></canvas>
                </div>
            </div>
        </el-dialog>

        <el-dialog title="找回密码" :visible.sync="SelectVisible" width="45%" @close="closeDialog1">
            <el-form>
                <el-form-item class="select-item">
                    <el-button class="select-item button" type="primary" @click="onPwd()">通过密保问题找回密码</el-button>
                    <el-button class="select-item button" type="danger" plain @click="onInfo()">通过个人信息找回密码</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>

        <el-dialog title="找回密码" :visible.sync="ForgetPwdVisible" width="45%" @close="closeDialog2">
            <el-form ref="form" :rules="rules" label-width="100px" class="box-content">
                <el-form-item label="账号:" prop="">
                    <!-- v-on:input="inputFunc"   //用于监听输入框的变化-->
                    <!--  @keyup.enter.native="handleSearch"   //用于监听回车键-->
                    <!-- v-on:input="inputFunc"   //用于监听光标的焦点-->
                    <!-- v-bind:disabled="dataForm.id!=0"  //动态绑定控件-->
                    <el-input
                        v-model="id"
                        placeholder="请输入账号"
                        class="handle-input mr10"
                        @keyup.enter.native="handleSearch"
                        id="idInput"
                        v-on:input="inputFunc"
                        @blur.native.capture="handleSearch"
                        clearable
                    ></el-input>
                    <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="idIsCheck"></el-button>
                    <!-- <el-button type="danger" icon="el-icon-close" circle class="item-check" v-else></el-button> -->
                </el-form-item>
                <el-form-item label="密码问题:">
                    <el-input placeholder="" v-model="form.question" :disabled="true"> </el-input>
                </el-form-item>

                <el-form-item label="密保答案:" prop="pwdAnswer">
                    <el-input
                        v-model="form.pwdAnswer"
                        placeholder="请输入密保答案"
                        class="handle-input mr10"
                        id="idInput1"
                        v-on:input="inputFunc1"
                        clearable
                    ></el-input>

                    <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="pwdIsCheck"></el-button>
                    <el-button type="danger" icon="el-icon-close" circle class="item-check" v-if="pwdNotCheck"></el-button>
                </el-form-item>
                <el-form-item label="重置密码:" prop="pwd">
                    <el-input placeholder="请输入重置密码" v-model="form.pwd" v-bind:disabled="!pwdIsCheck" show-password></el-input>
                </el-form-item>
                <el-form-item>
                    <el-button type="primary" @click="onSubmit()" v-if="pwdIsCheck">确认修改</el-button>
                    <el-button type="danger" plain @click="onCancel()">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>
        <el-dialog title="找回密码" :visible.sync="ForgetPwd1Visible" width="45%" @close="closeDialog3">
            <el-form ref="form" :rules="rules" label-width="100px" class="box-content">
                <el-form-item label="账号:" prop="">
                    <!-- v-on:input="inputFunc"   //用于监听输入框的变化-->
                    <!--  @keyup.enter.native="handleSearch"   //用于监听回车键-->
                    <!-- v-on:input="inputFunc"   //用于监听光标的焦点-->
                    <!-- v-bind:disabled="dataForm.id!=0"  //动态绑定控件-->
                    <el-input
                        v-model="id"
                        placeholder="请输入账号"
                        class="handle-input mr10"
                        @keyup.enter.native="handleSearch"
                        id="idInput3"
                        v-on:input="inputFunc"
                        @blur.native.capture="handleSearch"
                        clearable 
                    ></el-input>
                    <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="idIsCheck"></el-button>
                    <!-- <el-button type="danger" icon="el-icon-close" circle class="item-check" v-else></el-button> -->
                </el-form-item>

                <el-form-item label="身份证号码:" prop="pwdAnswer">
                    <el-input
                        v-model="form.cardID"
                        placeholder="请输入身份证号码"
                        class="handle-input mr10"
                        id="idInput4"
                        v-on:input="inputFunc2"
                        clearable
                    ></el-input>

                    <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="pwdIsCheck"></el-button>
                    <el-button type="danger" icon="el-icon-close" circle class="item-check" v-if="pwdNotCheck"></el-button>
                </el-form-item>

                <el-form-item label="姓名:" prop="pwdAnswer">
                    <el-input
                        v-model="form.userName"
                        placeholder="请输入姓名"
                        class="handle-input mr10"
                        id="idInput5"
                        v-on:input="inputFunc3"
                        clearable
                    ></el-input>

                    <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="nameIsCheck"></el-button>
                    <el-button type="danger" icon="el-icon-close" circle class="item-check" v-if="nameNotCheck"></el-button>
                </el-form-item>

                <el-form-item label="重置密码:" prop="pwd">
                    <el-input placeholder="请输入重置密码" v-model="form.pwd" v-bind:disabled="!allIsCheck" show-password></el-input>
                </el-form-item>

                <el-form-item>
                    <el-button type="primary" @click="onSubmit1()">确认修改</el-button>
                    <el-button type="danger" plain @click="onCancel1()">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>
        <el-dialog   
            title="提示"
            :visible.sync="Successdialog"
            :show-close="false"
            :close-on-click-modal="true"
            :close-on-press-escape="false"
            width="30%"
            center 
        >
            <span style="font-size: 18px; text-align: center; line-height: 18px">修改成功!{{ Sencond }}秒后返回登录界面</span>
            <span slot="footer" class="dialog-footer">
                <!-- //footer这里我只保留了一个按键，大家自由发挥 -->
                <el-button @click="sendMsg" type="primary" :disabled="isDisabled">立即关闭</el-button>
            </span>
        </el-dialog>
    </div>
</template>

<script>
require('tracking/build/tracking-min.js');
require('tracking/build/tracking.js');
require('tracking/build/data/face-min.js');
require('tracking/build/data/mouth-min.js');
require('tracking/build/data/eye-min.js');
require('tracking/examples/assets/stats.min.js');
export default {
    name: 'Login',
    inject: ['reload'],
    data: function () {
        return {
            param: {
                userID: '',
                passWord: '',
                userFlag: '0'
            },
            form: {
                question: '',
                pwdAnswer: '',
                rightAnswer: '',
                studentPassword: '',
                adminPassword: '',
                teacherPassword: '',
                pwd: '',
                userName: '',
                cardID: '',
                realName: '',
                studentName: '',
                teacherName: '',
                adminName: ''
            },

            face: {
                imgpath: ''
            },
            rules: {
                userID: [{ required: true, message: '请输入账号', trigger: 'blur' }],
                passWord: [{ required: true, message: '请输入密码', trigger: 'blur' }],
                userFlag: [{ required: true, message: '请选择用户类型', trigger: 'blur' }]
                // id: [{ required: true, message: '请输入账号', trigger: 'blur' }],
                // pwdAnswer: [{ required: true, message: '请输入密保答案', trigger: 'blur' }],
                //pwd: [{ required: true, message: '请输入密码', trigger: 'blur' }]
                // pwdNew: [{ required: true, message: '再次输入密码', trigger: 'blur' }]
            },
            Successdialog: false, //控制弹出
            Sencond: 3, //设置初始倒计时
            isDisabled: false,
            id: '',
            findUserUrl: '',
            updateOneUrl: '',
            SelectVisible: false,
            FaceLoginVisible: false,
            ForgetPwdVisible: false,
            ForgetPwd1Visible: false,
            idIsCheck: false,
            pwdIsCheck: false,
            pwdNotCheck: false,
            nameIsCheck: false,
            nameNotCheck: false,
            allIsCheck: false,
            idIsShow: false,
            videoEle: null,
            trackerTask: null,
            first: null,
            tips: '',
            str: ''
        };
    },
    methods: {
        submitForm() {
            this.$refs.login.validate((valid) => {
                if (valid) {
                    const that = this;
                    console.log("Login:");
                    this.$axios.post('/api/login', this.param).then((res) => {
                        /*   本身的路由  http://localhost:8088/ 但是为了后续方便修改，一般放置于 axios.js中 */
                        console.log(res);
                        const jwt = res.headers['authorization'];
                        const userInfo = res.data.data;

                        // 把数据共享出去，存于this.store下
                        that.$store.commit('SET_TOKEN', jwt);
                        that.$store.commit('SET_USERINFO', userInfo);

                        // 获取
                        //console.log(that.$store.getters.getUser);
                        if (res.data.code === 200) {
                            that.$router.push('/dashboard'); //跳转页
                            this.$message.success('登录成功');
                            //console.log(this.$store.getters.getUser)
                            this.TimeAndPlace();
                        }

                        if (res.data.code == 400) {
                            this.$message.error(res.data.msg);
                        }
                    });
                } else {
                    this.$message.error('请输入账号和密码');
                    // console.log('error submit!!');
                    return false;
                }
            });
        },
        resetForm(formName) {
            //this.$refs[formName].resetFields();
            this.param.userID = '';
            this.param.passWord = '';
        },
        faceLogin() {
            this.FaceLoginVisible = true;
            this.created();
        },
        forgetPwd() {
            //this.$router.push('/resetPwd');
            this.SelectVisible = true;
        },
        onPwd() {
            this.ForgetPwdVisible = true;
            //this.idIsShow=true;
        },
        onInfo() {
            this.ForgetPwd1Visible = true;
        },
        onSubmit() {
            const that = this; 
            this.id = this.form.userID;
            if (this.id != '' || this.id != null) {
                if (this.str === 'A') {
                    this.form.adminPassword = this.form.pwd;
                } else if (this.str === 'T') {
                    this.form.teacherPassword = this.form.pwd;
                } else {
                    this.form.studentPassword = this.form.pwd;
                }
            }

            if (this.form.pwd === '' || this.form.pwd == null) {
                this.$message.error('重置密码不能为空');
                this.idIsCheck = false;
            } else {
                this.$confirm('确定修改?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'info'
                })
                    .then(() => {
                        that.$axios
                            .post(that.updateOneUrl, that.form)
                            .then((res) => {
                                // console.log(res);
                                that.getSencond();
                            })
                            .catch((err) => {
                                console.error();
                            });
                    })
                    .catch(() => {});
            }
        },
        onCancel() {
            this.idIsCheck = false;
            this.idIsShow = false;
            this.pwdIsCheck = false;
            this.pwdNotCheck = false;
            this.form = '';
            this.id = '';
        },
        onSubmit1() {
            const that = this;
            if (this.id == '' || this.id == null) {
                this.$message.error('请输入必填项');
                this.onCancel1();
            } else {
                this.onSubmit();
            }
        },
        onCancel1() {
            this.idIsCheck = false;
            this.idIsShow = false;
            this.pwdIsCheck = false;
            this.pwdNotCheck = false;
            this.nameNotCheck = false;
            this.nameIsCheck = false;
            this.form = '';
            this.id = '';
        },
        //关闭弹框的事件
        closeDialog() {
            this.FaceLoginVisible = false;
            this.closeCamera(); //清空数据
        },
        //关闭弹框的事件
        closeDialog1() {
            this.SelectVisible = false;
            this.reload(); //刷新 ----推荐
        },
        //关闭弹框的事件
        closeDialog2() {
            this.idIsShow = false;
            this.form = '';
            this.id = '';
        },
        //关闭弹框的事件
        closeDialog3() {
            this.onCancel1();
        },
        created() {
            setTimeout(() => {
                this.openCamera(); // 此为绘画canvas的方法调用
                this.tips = '初始化摄像头';
            }, 500);
        },
        // 触发搜索按钮
        handleSearch() {
            const that = this;
            //console.log(this.id); //打印输入搜索的值
            if (this.id == '' || this.id == null) {
                //str = this.form.id.slice(0);//返回整个字符串
                this.str = this.id.substring(0, 1); //打印输入值的首个字符
            }
            if (this.str === 'A') {
                this.findUserUrl = '/api/admin/findAdminByID';
                this.updateOneUrl = '/api/admin/updateOne';
            } else if (this.str === 'T') {
                this.findUserUrl = '/api/teacher/findTeacherByID';
                this.updateOneUrl = '/api/teacher/updateOne';
            } else {
                this.findUserUrl = '/api/student/findStudentByID';
                this.updateOneUrl = '/api/student/updateOne';
            }

            this.$axios
                .get(this.findUserUrl, { params: { id: this.id } })
                .then((res) => {
                    console.log(res);
                    this.form = res.data[res.data.length - 1];
                    if (this.str === 'A') {
                        this.form.realName = this.form.adminName;
                    } else if (this.str === 'T') {
                        this.form.realName = this.form.teacherName;
                    } else {
                        this.form.realName = this.form.studentName;
                    }

                    if (this.form.userID === '' || this.form.userID) {
                        this.$message.error('用户不存在');
                    } else {
                        this.idIsCheck = true;
                    }

                    this.form.rightAnswer = this.form.answer;
                    this.idIsShow = true;
                })
                .catch((err) => {
                    this.idIsCheck = false;
                    this.$message.error('用户不存在');
                });
        },
        //监听事件-输入框
        inputFunc(e) {
            if (this.id == '' || this.id == null) {
                this.form = '';
            }
        },
        //监听事件-输入框
        inputFunc1(e) {
            // console.log(this.form.rightAnswer);
            if (this.form.rightAnswer === this.form.pwdAnswer) {
                this.pwdIsCheck = true;
                this.pwdNotCheck = false;
            } else {
                this.pwdIsCheck = false;
                this.pwdNotCheck = true;
            }
        },
        //监听事件-输入框
        inputFunc2(e) {
            // console.log(this.form.rightAnswer);
            if (this.form.cardID === this.form.cardNo) {
                this.pwdIsCheck = true;
                this.pwdNotCheck = false;
            } else {
                this.pwdIsCheck = false;
                this.pwdNotCheck = true;
            }
        },
        //监听事件-输入框
        inputFunc3(e) {
            if (this.form.userName === this.form.realName) {
                this.nameIsCheck = true;
                this.nameNotCheck = false;
            } else {
                this.nameIsCheck = false;
                this.nameNotCheck = true;
            }
            if (this.idIsCheck && this.pwdIsCheck && this.nameIsCheck) {
                this.allIsCheck = true;
            } else {
                this.allIsCheck = false;
            }
        },
        mounted() {},
        openCamera() {
            var video = document.getElementById('video');
            var canvas = document.getElementById('canvas');
            var context = this.$refs['canvas'].getContext('2d');
            var tracker = new tracking.ObjectTracker('face'); // 引入第三方库  cnpm install tracking --save
            tracker.setInitialScale(1);
            tracker.setStepSize(2);
            tracker.setEdgesDensity(0.1);

            this.trackerTask = tracking.track('#video', tracker, { camera: true });
            //-------  指定 canvas 的宽高 ，auto 自动播放
            let constraints = {
                video: { width: 500, height: 500 },
                audio: true
            };

            let promise = navigator.mediaDevices.getUserMedia(constraints); // h5 新的API

            promise
                .then(function (MediaStream) {
                    video.srcObject = MediaStream;
                    video.play();
                })
                .catch(function (PermissionDeniedError) {
                    console.log(PermissionDeniedError);
                });
            //--------------
            let that = this;
            that.tracker_fun(tracker, video, context, canvas); //open 摄像头，执行tracker_fun( 传入参数 )
        },
        tracker_fun(tracker, video, context, canvas) {
            let that = this;
            let set_clear;
            let flag = true;
            set_clear = setTimeout(function () {
                // 每秒 检测人脸 结果
                tracker.on('track', function (event) {
                    that.tips = '正在刷脸中';
                    // 视频流
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    event.data.forEach(function (rect) {
                        context.strokeStyle = '#ff0000';
                        context.strokeRect(rect.x, rect.y, rect.width, rect.height);
                    });
                    if (event.data.length) {
                        // 会不停的去检测人脸，所以这里需要做个锁
                        if (flag) {
                            // 裁剪出人脸并绘制下来
                            const canvasUpload = document.getElementById('canvas');
                            const contextUpload = canvasUpload.getContext('2d');
                            contextUpload.drawImage(video, 0, 0, 480, 400);
                            flag = false;
                            // 人脸的basa64
                            that.face.imgpath = canvasUpload.toDataURL('image/jpeg');
                            // console.log(that.face);

                            // ajax请求
                            that.$axios
                                .post('/api/faceLogin', JSON.stringify(that.face), {
                                    headers: {
                                        'Content-Type': 'application/json; charset=UTF-8'
                                    }
                                })
                                .then((res) => {
                                    //console.log(res);
                                    const jwt = res.headers['authorization'];
                                    const userInfo = res.data;

                                    // 把数据共享出去，存于this.store下
                                    that.$store.commit('SET_TOKEN', jwt);
                                    that.$store.commit('SET_USERINFO', userInfo);
                                    //console.log(userInfo)
                                    if (res.data.error_code === 0 && res.data.face_liveness > 0.8) {
                                        that.closeCamera();
                                        // 登录成功跳转到首页
                                        that.$router.push('/dashboard');
                                        that.$message.success('登录成功');
                                        that.FaceLoginVisible = false;
                                    } else {
                                        // 登录失败重新进行人脸检测
                                        // continue;
                                        //that.$message.fail('记录风险');
                                    }
                                })
                                .catch((err) => {
                                    console.log(err);
                                });
                            setTimeout(() => { 
                                //设置延迟执行
                                video.load();
                                that.first = null;
                                that.tracker_fun(tracker, video, context, canvas);
                            }, 2000);
                        }
                    } else {
                        that.tips = '没有检测到人脸';
                    }
                });
                clearTimeout(set_clear);
                this.tips = '重新加载摄像头';
            }, 3000);
        },
        // 关闭摄像头
        closeCamera() {
            if (!this.$refs['video'].srcObject) return;
            let stream = this.$refs['video'].srcObject;
            let tracks = stream.getTracks();
            tracks.forEach((track) => {
                track.stop();
            });
            this.$refs['video'].srcObject = null;
        },
        TimeAndPlace() {
            const that = this;
            this.$store.getters.getUser.loginTime=''; 
            this.$axios.post('/api/accountrecords/timeAndPlace', this.$store.getters.getUser).then((res) => {});
        },
        getSencond() {
            const that = this;
            that.Successdialog = true;
            const interval = window.setInterval(function () {
                --that.Sencond;
                if (that.Sencond === 0) {
                    that.isDisabled = false;
                    that.Successdialog = false;
                    window.clearInterval(interval);
                    that.sendMsg(); //倒计时结束时运行的业务逻辑，这里的是关闭当前页面
                }
            }, 1000);
        },
        sendMsg() {
            //window.close();
            //删除session缓存信息
            this.ForgetPwdVisible = false;
            this.SelectVisible = false;  
            this.ForgetPwd1Visible = false;
            this.$store.commit('REMOVE_INFO');
            this.$router.push('/login');
        }
    }
};
</script>

<style scoped>
.login-wrap {
    position: relative;
    width: 100%;
    height: 100%;
    background-image: url(../assets/image/login-bg.jpg);
    background-size: 100%;
}
.ms-title {
    width: 100%;
    line-height: 50px;
    text-align: center;
    font-size: 30px;
    color: rgb(15, 15, 15);
    border-bottom: 1px solid #ddd;
}
.ms-login {
    position: absolute;
    left: 50%;
    top: 50%;
    width: 350px;
    margin: -190px 0 0 -175px;
    border-radius: 5px;
    background: rgba(255, 255, 255, 0.3);
    overflow: hidden;
}
.ms-content {
    padding: 30px 30px;
}
.login-btn {
    color: blue;
    text-align: center;
}
.login-btn button {
    width: 100%;
    height: 36px;
    margin-bottom: 10px;
}
.login-tips {
    position: absolute;
    font-size: 12px;
    line-height: 30px;
    color: #fff;
}
.login-tips.text {
    color: blue;
    size: 30px;
}
.userFlag {
    /* 垂直居中 */
    display: flex;
    justify-content: center;

    /* 水平居中 */
    /* display: flex;
  justify-content: center;
  align-items: center; */

    /* 垂直水平居中 */
    /* display: flex;
  align-items: center; */
}

.btn-txt button {
    position: relative;
    color: blue;
    size: 30px;
}
.btn-right {
    left: 180px;
}
.tishi {
    font-size: 20px;
    text-align: center;
}
.select-item {
    font-size: 18px;
    position: relative;
    text-align: center;
}
.box-content {
    position: relative;
    text-align: center;
    display: inline-block;
    padding: 0 100px 0 0;
}
.item-check {
    position: absolute;
    padding: 0 0 0 0;
    margin-top: 10px;
    margin-right: 10px;
    margin-bottom: 10px;
    margin-left: 5px;
}
</style>