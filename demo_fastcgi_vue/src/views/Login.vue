<template>

    <div class="login-wrap">
        <div class="ms-login">
            <div class="ms-title">IOT设备控制管理系统</div>
            <el-form :model="param" :rules="rules" ref="login" label-width="0px" class="ms-content">
                <el-form-item prop="accountNumber">
                    <el-input v-model="param.accountNumber" placeholder="账号">
                        <el-button slot="prepend" icon="el-icon-lx-people"></el-button>
                    </el-input>
                </el-form-item>
                <el-form-item prop="passWord">
                    <el-input type="passWord" placeholder="密码" v-model="param.passWord" @keyup.enter.native="submitForm()">
                        <el-button slot="prepend" icon="el-icon-lx-lock"></el-button>
                    </el-input>
                </el-form-item>

                <!-- <el-form-item prop="userFlag">
                    <div class="userFlag">
                        <el-radio v-model="param.userFlag" label="0">学生</el-radio>
                        <el-radio v-model="param.userFlag" label="1">教师</el-radio>
                        <el-radio v-model="param.userFlag" label="2">管理员</el-radio>
                    </div>
                </el-form-item> -->

                <div class="login-btn">
                    <el-button type="primary" @click="submitForm('param')">登录</el-button>
                </div>
                <div class="login-btn">
                    <el-button type="primary" @click="resetForm('param')">重置</el-button>
                </div>

                <div class="btn-txt">
                    <el-button type="text" @click="forgetPwd">忘记密码</el-button>
                    <el-button class="btn-right" type="text" @click="faceLogin">注册账号</el-button>
                </div>
                <!-- <div class="login-tips">
                    <p class="text">Tips : 若无账号则联系管理员</p>
                </div> -->
            </el-form>
        </div>


        <el-dialog title="找回密码" :visible.sync="SelectVisible" width="45%" @close="closeDialogOfSelectVisible">
            <el-form>
                <el-form-item class="select-item">
                    <!-- <el-button class="select-item button" type="primary" @click="onPwd()">通过密保问题找回密码</el-button> -->
                    <el-button class="select-item button" type="danger" plain @click="onInfo()">通过个人信息找回密码</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>

        <el-dialog title="通过信息校验修改密码" :visible.sync="ForgetPwdVisible" width="45%" @close="closeDialogOfInfoCheck">
            <el-form :model="infoForm" ref="infoForm" :rules="rules_checkInfo" label-width="100px" class="box-content">
                <el-form-item label="账号:" prop="accountNumber">
                    <!-- v-on:input="inputFunc"   //用于监听输入框的变化-->
                    <!--  @keyup.enter.native="handleSearch"   //用于监听回车键-->
                    <!-- v-on:input="inputFunc"   //用于监听光标的焦点-->
                    <!-- v-bind:disabled="dataForm.id!=0"  //动态绑定控件-->
                    <el-input
                        v-model.trim="infoForm.accountNumber"
                        placeholder="请输入账号"
                        class="handle-input mr10"
                        id="idInput3"
                        v-on:input="inputFunc"
                        clearable 
                    ></el-input>
                    <!-- <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="isInfoFormCheck"></el-button> -->
                    <!-- <el-button type="danger" icon="el-icon-close" circle class="item-check" v-else></el-button> -->
                </el-form-item>

                <el-form-item label="身份证号码:" prop="cardID">
                    <el-input
                        v-model.trim="infoForm.cardID"
                        placeholder="请输入身份证号码"
                        class="handle-input mr10"
                        id="idInput4"
                        v-on:input="inputFunc2"
                        clearable
                    ></el-input>

                    <!-- <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="pwdisInfoFormCheck"></el-button>
                    <el-button type="danger" icon="el-icon-close" circle class="item-check" v-if="pwdNotCheck"></el-button> -->
                </el-form-item>
                <!-- v-model.trim 表单检验里去掉输入框的前后空格 -->
                <el-form-item label="姓名:" prop="userName">
                    <el-input
                        v-model.trim="infoForm.userName"
                        placeholder="请输入姓名"
                        class="handle-input mr10"
                        id="idInput5"
                        v-on:input="inputFunc3"
                        clearable
                    ></el-input>

                    <!-- <el-button type="success" icon="el-icon-check" circle class="item-check" v-if="nameisInfoFormCheck"></el-button>
                    <el-button type="danger" icon="el-icon-close" circle class="item-check" v-if="nameNotCheck"></el-button> -->
                </el-form-item>

                <el-form-item>
                    <el-button type="primary" @click="onSubmitInfoCheck()">信息校验</el-button>
                    <el-button type="danger" plain @click="onCancelInfoCheck()">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>


        <el-dialog title="修改密码" :visible.sync="ForgetPwdVisible1" width="45%" @close="closeDialogOfForgetPwdVisible1">
            <el-form ref="forgetPwd" :rules="rules_checkPwd" label-width="100px" class="box-content">
                <el-form-item label="新密码:" prop="newPassword">
                    <el-input placeholder="请输入重置密码" v-model.trim="passwordForm.newPassword" show-password></el-input>
                </el-form-item>
                <el-form-item label="确认密码:" prop="checkPassWord">
                    <el-input placeholder="再次请输入重置密码" v-model.trim="passwordForm.checkPassWord" show-password></el-input>
                </el-form-item>

                <el-form-item>
                    <el-button type="primary" @click="onSubmitUpdatePassword()">确认修改</el-button>
                    <el-button type="danger" plain @click="onRestPasswordForm()">取消</el-button>
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
                accountNumber: '',
                passWord: '',
            },
            infoForm: {
                accountNumber: '',
                passWord: '',
                userName: '',
                cardID: '',
            },
            passwordForm:{
                newPassWord: '',
                checkPassWord: '',
            },

            face: {
                imgpath: ''
            },
            rules: {
                accountNumber: [{ required: true, message: '请输入账号', trigger: 'blur' }],
                passWord: [{ required: true, message: '请输入密码', trigger: 'blur' }],
             },
            rules_checkInfo: {
                accountNumber: [{ required: true, message: '请输入账号', trigger: 'blur' }],
                cardID: [{ required: true, message: '请输入身份证号', trigger: 'blur' }],
                userName: [{ required: true, message: '请输入姓名', trigger: 'blur' }],
            },

            rules_checkPwd:{
                
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
            ForgetPwdVisible1: false,
            isInfoFormCheck: false,
            pwdisInfoFormCheck: false,
            pwdNotCheck: false,
            nameisInfoFormCheck: false,
            nameNotCheck: false,
            allisInfoFormCheck: false,
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
                    //this.$axios.post('/api/login', this.param, {headers: {'Content-Type': 'multipart/form-data'}}).then((res) => {
                    this.$axios.post('/api/login', this.param, {headers: {'Content-Type': 'application/json'}}).then((res) => {
                        /*   本身的路由  http://localhost:8088/ 但是为了后续方便修改，一般放置于 axios.js中 */
                        // console.log(res);
                        const jwt = res.headers['authorization'];
                        const userInfo = res.data;
                        // console.log(userInfo);
                        // 把数据共享出去，存于this.store下
                        that.$store.commit('SET_TOKEN', jwt);
                        that.$store.commit('SET_USERINFO', userInfo);

                        // 获取 
                        //console.log(that.$store.getters.getUser);
                        if (res.status === 200) {
                            if(userInfo.data === 1){
                                that.$router.push('/dashboard'); //跳转页
                                this.$message.success(res.data.msg);
                            }else{
                                this.$message.error(res.data.msg);
                            }
                        }
                    })
                    .catch(error => {
                        // 请求失败后的处理逻辑
                        if (error.response && error.response.status) {
                            this.$message.error(error.response.status +" "+ error.response.statusText);
                            // console.error('500 (Internal Server Error)', error.response.data);
                            // console.error('message', error.message);
                            // console.error('headers', error.response.headers);
                            // console.error('statusText', error.response.statusText);
                            // console.error('config', error.response.config);
                            
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
            this.param.accountNumber = '';
            this.param.passWord = '';
        },
        faceLogin() {
            this.FaceLoginVisible = true;
            this.created();
        },
        forgetPwd() {
            this.SelectVisible = true;
        },

        onInfo() {
            this.ForgetPwdVisible = true;
        },
        isInfoFormChecking(){
            if (this.infoForm.accountNumber === '' || this.infoForm.accountNumber === null) 
            {
                this.$message.error('必填项不能为空');
                this.isInfoFormCheck = false;
            }else if(this.infoForm.cardID === '' || this.infoForm.cardID === null)
            {
                this.$message.error('必填项不能为空');
                this.isInfoFormCheck = false;
            }else if(this.infoForm.userName === '' || this.infoForm.userName === null)
            {
                this.$message.error('必填项不能为空');
                this.isInfoFormCheck = false;
            }else{
                this.isInfoFormCheck = true;
            }
            return this.isInfoFormCheck; 
        },
        onSubmitInfoCheck() {
            const that = this; 
            this.$refs.infoForm.validate((valid) => {
                if (valid) {
                    const that = this;
                    this.$axios.post('/api/infoCheck', this.infoForm, {headers: {'Content-Type': 'application/json'}}).then((res) => {
                        const jwt = res.headers['authorization'];
                        const pRes = res.data;
                        console.log(pRes);

                        // 获取 
                        //console.log(that.$store.getters.getUser);
                        if (res.status === 200) {
                            if(pRes.status === 0){
                                this.ForgetPwdVisible1 = true;
                            }else{
                                if((pRes.status) & 1){
                                    setTimeout(() => {
                                        this.$message.error("此账号不存在!");
                                    }, 10);
                                    that.infoForm.accountNumber = '';
                                    that.infoForm.cardID = '';
                                    that.infoForm.userName = '';
                                }
                                if(((pRes.status >> 1) & 1) || ((pRes.status >> 2) & 1)){
                                    setTimeout(() => {
                                        this.$message.error("身份证号码/姓名校验失败！");
                                    }, 10);
                                    that.infoForm.cardID = '';
                                    that.infoForm.userName = '';
                                }
                            }
                        }
                    })
                    .catch(error => {
                        // 请求失败后的处理逻辑
                        if (error.response && error.response.status) {
                            this.$message.error(error.response.status +" "+ error.response.statusText);
                        }
                    });
                } else {
                    // this.$message.error('请输入必填项');
                    return false;
                }
            });
        },

        onCancelInfoCheck() {
            const that = this;
            that.isInfoFormCheck = false;
            that.infoForm.accountNumber = '';
            that.infoForm.cardID = '';
            that.infoForm.userName = '';
        },
        
        onSubmitUpdatePassword() {
            const that = this;
            if (this.isInfoFormChecking()) {
                this.$confirm('确定修改?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'info'
                })
                .then(() => {
                    that.$axios
                        .post(that.updateOneUrl, that.form)
                        .then((res) => {this.infoForm
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
        onRestPasswordForm() {
            this.ForgetPwdVisible1 = false;
            // this.isInfoFormCheck = true;
            this.passwordForm.newPassWord = '';
            this.passwordForm.cheackPassWord = '';
        },
        //关闭弹框的事件
        closeDialog() {
            this.FaceLoginVisible = false;
            this.closeCamera(); //清空数据
        },
        //关闭弹框的事件
        closeDialogOfSelectVisible() {
            this.SelectVisible = false;
            this.reload(); //刷新 ----推荐
        },

        //关闭弹框的事件
        closeDialogOfInfoCheck() {
            this.onCancelInfoCheck();
        },

        //关闭弹框的事件
        closeDialogOfForgetPwdVisible1() {
            this.onRestPasswordForm();
        },


        // 触发搜索按钮
        handleSearch() {
            const that = this;
            //console.log(this.id); //打印输入搜索的值
            if (this.infoForm.accountNumber == '' || this.infoForm.accountNumber == null) {
                //str = this.infoForm.id.slice(0);//返回整个字符串
                this.str = this.infoForm.accountNumber.substring(0, 1); //打印输入值的首个字符
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
                .get(this.findUserUrl, { params: { id: this.infoForm.accountNumber } })
                .then((res) => {
                    console.log(res);
                    this.infoForm = res.data[res.data.length - 1];
                    if (this.str === 'A') {
                        this.infoForm.realName = this.infoForm.adminName;
                    } else if (this.str === 'T') {
                        this.infoForm.realName = this.infoForm.teacherName;
                    } else {
                        this.infoForm.realName = this.infoForm.studentName;
                    }

                    if (this.infoForm.accountNumber === '' || this.infoForm.accountNumber) {
                        this.$message.error('用户不存在');
                    } else {
                        this.isInfoFormCheck = true;
                    }

                    this.infoForm.rightAnswer = this.infoForm.answer;
                    this.idIsShow = true;
                })
                .catch((err) => {
                    this.isInfoFormCheck = false;
                    this.$message.error('用户不存在');
                });
        },
        //监听事件-输入框
        inputFunc(e) {
            if (this.infoForm.accountNumber == '' || this.infoForm.accountNumber == null) {
                this.infoForm.accountNumber = '';
            }
        },
        //监听事件-输入框
        inputFunc1(e) {
            // console.log(this.infoForm.rightAnswer);
            if (this.infoForm.rightAnswer === this.infoForm.pwdAnswer) {
                this.pwdisInfoFormCheck = true;
                this.pwdNotCheck = false;
            } else {
                this.pwdisInfoFormCheck = false;
                this.pwdNotCheck = true;
            }
        },
        //监听事件-输入框
        inputFunc2(e) {
            if (this.infoForm.cardID === '' || this.infoForm.cardID === null) {
                this.infoForm.cardID = '';
            }
        },
        //监听事件-输入框
        inputFunc3(e) {
            if (this.infoForm.userName === '' || this.infoForm.userName === null) {
                this.infoForm.userName = '';
            }
        },
        mounted() {},

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
            //this.ForgetPwdVisible = false;
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