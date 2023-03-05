<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i> 账户安全设置 </el-breadcrumb-item>
                <el-breadcrumb-item>修改密保</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="form-box">
                <el-form ref="form" :model="form" :rules="rules" label-width="280px" class="box-content">
                    <el-form-item label="密码问题:" v-if="form.isOrNot">
                        <el-input placeholder="" v-model="form.question" :disabled="true"> </el-input>
                        <el-button type="text" @click="onChange()" class="onChange" v-if="form.isShow">修改</el-button>
                        <!-- <el-button plain @click="onCancel('form')" class="cancel">修改</el-button> -->
                    </el-form-item>

                    <el-form-item label="密码问题:" v-else>
                        <el-select v-model="form.questions" placeholder="请选择" @change="getValue">
                            <el-option key="0" label="你最喜欢的数字" value="你最喜欢的数字"></el-option>
                            <el-option key="1" label="你最喜欢的水果" value="你最喜欢的水果"></el-option>
                            <el-option key="3" label="你最喜欢的动物" value="你最喜欢的动物"></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="密保答案:" prop="pwdAnswer">
                        <el-input placeholder="请输入密保答案" v-model="form.pwdAnswer" clearable> </el-input>
                    </el-form-item>

                    <el-form-item>
                        <el-button type="primary" @click="onSubmit('form')">确认更新</el-button>
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
                    <span style="font-size: 18px;text-align:center;line-height:18px; ">修改成功!{{ Sencond }}秒后刷新页面</span>
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
    inject: ['reload'],
    name: 'changePwdN',
    data() {
        return {
            form: {
                question: '',
                pwdAnswer: '',
                answer: '',
                isShow: false,
                isOrNot: false,
                questions: ''
            },
            findUserUrl: '',
            updateOneUrl: '',
            clearFlag: false,
            rules: {
                pwdAnswer: [{ required: true, message: '请输入密保答案', trigger: 'blur' }]
            },
            Successdialog: false, //控制弹出
            Sencond: 3, //设置初始倒计时
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
                if (res.data[res.data.length - 1].question == null || res.data[res.data.length - 1].question == '') {
                    this.form.isOrNot = false;
                    this.form.isShow = false;
                } else {
                    this.form.isOrNot = true;
                    this.form.isShow = true;
                }
                //this.form.rightAnswer = res.data[res.data.length - 1].answer;
            })
            .catch((err) => {
                console.log(err);
            });
    },
    methods: {
        onSubmit() {
            const that = this;
            this.form.question = this.form.questions;
            this.form.answer = this.form.pwdAnswer;
            //console.log(this.form);
            this.$refs.form.validate((valid) => {
                if (valid) {
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
                }
            });
        },
        onCancel() {
            this.reload(); //刷新 ----推荐
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
            this.reload(); //刷新 ----推荐
            //this.$router.go(0);//刷新
            // location.reload(); //刷新
        },
        onChange() {
            this.form.question = '';
            this.form.isOrNot = false;
            this.form.isShow = false;
        },
        //value的是是:value的值
        getValue(value) {
            let that = this;
            this.form.clearFlag = true;
            //console.log(value);
            if (this.form.clearFlag) {
                //this.form.pwdAnswer = '';
                this.form.clearFlag = false;
            }
        }
    }
};
</script>

<style scoped>
.container {
    position: relative;
    width: 100%;
    height: 100%;
    padding: 30px 30px 250px;
}
.onChange {
    position: absolute;
    right: -50px;
}
</style>