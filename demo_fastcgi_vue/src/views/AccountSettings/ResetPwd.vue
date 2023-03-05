<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item>
                    <i class="el-icon-lx-calendar"></i> 账户安全设置
                </el-breadcrumb-item>
                <el-breadcrumb-item>修改密保</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="form-box">
                <el-form ref="form" :model="form" :rules="rules" label-width="280px" class="box-content">
                    <el-form-item label="密码问题:">
                        <el-input placeholder="" v-model="form.question" :disabled="true"> </el-input>
                    </el-form-item>

                    <el-form-item label="密保答案:" prop="pwdAnswer">
                        <el-input placeholder="请输入密保答案" v-model="form.pwdAnswer" clearable> </el-input>
                    </el-form-item>

                    <el-form-item label="密码:" prop="pwd">
                        <el-input placeholder="请输入密码" v-model="form.pwd" show-password></el-input>
                    </el-form-item>
                    <el-form-item label="确认密码:" prop="pwdNew">
                        <el-input placeholder="请再次输入密码" v-model="form.pwdNew" show-password></el-input>
                    </el-form-item>

                    <el-form-item>
                        <el-button type="primary" @click="onSubmit('form')">表单提交</el-button>
                        <el-button type="danger" plain @click="onCancel('form')">取消</el-button>
                    </el-form-item>
                </el-form>
                <!-- :show-close= false //不要小叉叉关闭 
                :close-on-click-modal= true //不要点击遮罩层关闭 
                :close-on-press-escape= false
                //不要esc关闭 width="30%" //宽度 -->
                <el-dialog
                    title="提示"
                    :visible.sync="Successdialog"
                    :show-close="false"
                    :close-on-click-modal="true"
                    :close-on-press-escape="false"
                    width="30%"
                    center
                >
                    <span style="font-size: 18px">修改密码成功！{{ Sencond }}秒后关闭页面,重新登录。</span>
                    <span slot="footer" class="dialog-footer">
                        <!-- //footer这里我只保留了一个按键，大家自由发挥 -->
                        <el-button @click="sendMsg" type="primary" :disabled="isDisabled">立即关闭</el-button>
                    </span>
                </el-dialog>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'baseform',
    data() {
        return { 
            form: {
                question: '',
                pwdAnswer: '',
                rightAnswer: '',
                studentPassword: '',
                adminPassword: '',
                teacherPassword: '',
                pwd: '',
                pwdNew: ''
            },
            findUserUrl: '',
            updateOneUrl: '',
            rules: {
                pwdAnswer: [{ required: true, message: '请输入密保答案', trigger: 'blur' }],
                pwd: [{ required: true, message: '请输入密码', trigger: 'blur' }],
                pwdNew: [{ required: true, message: '再次输入密码', trigger: 'blur' }]
            },
            Successdialog: false, //控制弹出
            Sencond: 5, //设置初始倒计时
            isDisabled: false
        };
    },
    //  或者使用做个地址请求 '/api/student/findStudentByID?id=1'
    created() {
        if (this.$store.getters.getUser.roseID === '0') {
            this.findUserUrl = '/api/student/findStudentByID';
            this.updateOneUrl = '/api/student/updateOne';
        } else if (this.$store.getters.getUser.roseID === '1') {
            this.findUserUrl = '/api/teacher/findTeacherByID';
            this.updateOneUrl = '/api/teacher/updateOne';
        } else {
            this.findUserUrl = '/api/admin/findAdminByID';
            this.updateOneUrl = '/api/admin/updateOne';
        }
        this.$axios
            .get(this.findUserUrl, { params: { id: this.$store.getters.getUser.userID } })
            .then((res) => {
                //console.log(res.data);
                this.form = res.data[res.data.length - 1];
                this.form.rightAnswer = res.data[res.data.length - 1].answer;
            })
            .catch((err) => {
                console.log(err);
            });
    },
    methods: {
        onSubmit() {
            const that = this;
            this.$refs.form.validate((valid) => {
                if (valid) {
                    if (this.form.pwd == this.form.pwdNew) {
                        if (this.form.rightAnswer == this.form.pwdAnswer) {
                            this.form.studentPassword = this.form.pwdNew;
                            this.form.teacherPassword = this.form.pwdNew;
                            this.form.adminPassword = this.form.pwdNew;
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
                                            that.$message.error(`修改失败`);
                                        });
                                })
                                .catch(() => {});
                        } else {
                            this.$message.error('密保答案错误，请正确输入！');
                        }
                    } else {
                        this.$message.error('两次密码输入不一致');
                        this.form.pwdNew = '';
                        this.form.pwd = '';
                    }
                }
            });
        },
        onCancel() {
            this.form.pwdAnswer = '';
            this.form.pwdNew = '';
            this.form.pwd = '';
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
            this.$store.commit('REMOVE_INFO');
            this.$router.push('/login');
        }
    }
};
</script>

<style scoped>
.container {
    position: relative;
    width: 100%;
    height: 100%;
    padding: 30px 30px;
}
</style>