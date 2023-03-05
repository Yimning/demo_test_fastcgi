<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i> 课程管理 </el-breadcrumb-item>
                <el-breadcrumb-item>添加课程</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <el-button type="info" icon="el-icon-download" @click="onUpload">外部导入</el-button>
            <div class="form-box">
                <el-form ref="form" :model="form" :rules="rules" label-width="280px" class="box-content">
                    <el-form-item label="课程号:" prop="courseID">
                        <el-input
                            placeholder="请输入课程号"
                            v-model="form.courseID"
                            @keyup.enter.native="handleSearch"
                            id="idInput"
                            @blur.native.capture="handleSearch"
                            clearable
                        >
                        </el-input>
                    </el-form-item>

                    <el-form-item label="课程名称:" prop="courseName">
                        <el-input placeholder="请输入课程名称" v-model="form.courseName" clearable> </el-input>
                    </el-form-item>

                    <el-form-item label="每周:" prop="courseDay">
                        <el-select v-model="form.courseDay" placeholder="请选择">
                            <el-option
                                @change="handleChange5"
                                el-option
                                v-for="item in weekOptions"
                                :key="item.value"
                                :label="item.label"
                                :value="item.value"
                            ></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="上课时间:" prop="courseTime">
                        <el-time-select
                            :span="11"
                            v-model="form.courseTime"
                            :picker-options="{
                                start: '08:00',
                                step: '00:05',
                                end: '21:05'
                            }"
                            placeholder="选择时间"
                        >
                        </el-time-select>
                    </el-form-item>
                    <el-form-item label="上课地点:" prop="classRoomID">
                        <el-select v-model="form.classRoomID" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.options"
                                :key="item.classRoomID"
                                :label="item.classRoomName"
                                :value="item.classRoomName"
                            ></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="起始节:" prop="coursePeriodF" class="perid">
                        <el-input-number v-model="form.coursePeriodF" @change="handleChange1" :min="1" :max="12"></el-input-number>
                        <el-input-number
                            class="perid-right"
                            v-model="form.coursePeriodB"
                            @change="handleChange2"
                            :min="1"
                            :max="12"
                        ></el-input-number>
                        <el-col class="line" :span="4">-</el-col>
                    </el-form-item>
                    <el-form-item label="起始周:" prop="courseWeekF" class="perid">
                        <el-input-number v-model="form.courseWeekF" @change="handleChange3" :min="1" :max="25"></el-input-number>
                        <el-input-number
                            class="perid-right"
                            v-model="form.courseWeekB"
                            @change="handleChange4"
                            :min="1"
                            :max="25"
                        ></el-input-number>
                        <el-col class="line" :span="4">-</el-col>
                    </el-form-item>
                    <el-form-item label="课程说明:">
                        <el-input placeholder="选填" v-model="form.courseNote"> </el-input>
                    </el-form-item>
                    <el-form-item>
                        <el-button type="primary" @click="onSubmit('form')">确认修改</el-button>
                        <el-button type="danger" plain @click="onCancel('form')">取消</el-button>
                    </el-form-item>
                </el-form>

                <el-dialog
                    title="提示"
                    :visible.sync="Successdialog"
                    :show-close="false"
                    :close-on-click-modal="true"
                    :close-on-press-escape="false"
                    width="30%"
                    center
                >
                    <span style="font-size: 18px">课程已添加！{{ Sencond }}秒后关闭页面并刷新。</span>
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
    inject: ['reload'],
    data() {
        return {
            weekOptions: [
                { value: '1', label: '星期一' },
                { value: '2', label: '星期二' },
                { value: '3', label: '星期三' },
                { value: '4', label: '星期四' },
                { value: '5', label: '星期五' },
                { value: '6', label: '星期六' },
                { value: '7', label: '星期天' }
            ],

            form: {
                options: [],
                coursePeriodF: 1,
                coursePeriodB: 3,
                courseWeekF: 1,
                courseWeekB: 18
            },
            findUserUrl: '',
            updateOneUrl: '',
            rules: {
                courseID: [{ required: true, message: '必填', trigger: 'blur' }],
                courseName: [{ required: true, message: '必填', trigger: 'blur' }],
                courseDay: [{ required: true, message: '必填', trigger: 'blur' }],
                courseTime: [{ required: true, message: '必填', trigger: 'blur' }],
                classRoomID: [{ required: true, message: '必填', trigger: 'blur' }],
                coursePeriodF: [{ required: true, message: '必填', trigger: 'blur' }],
                courseWeekF: [{ required: true, message: '必填', trigger: 'blur' }]
            },
            Successdialog: false, //控制弹出
            Sencond: 5, //设置初始倒计时
            isDisabled: false
        };
    },
    //  或者使用做个地址请求 '/api/student/findStudentByID?id=1'
    created() {
        this.findUserUrl = '/api/classroom/findAllClassroom';
        this.updateOneUrl = '/api/course/add';
        if (this.$store.getters.getUser.roseName == '教师管理员') {
            this.$axios
                .get(this.findUserUrl)
                .then((res) => {
                    // console.log(res.data);
                    this.form.options = res.data;
                })
                .catch((err) => {
                    console.log(err);
                });
        } else {
            this.$message.error(`无权限访问！`);
            this.$router.push('/403');
        }
    },
    methods: {
        onSubmit() {
            const that = this;
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
        },

        handleSearch() {
            const that = this;
            if (this.form.courseID != '' || this.form.courseID != null) {
                this.findUserUrl = '/api/course/findCourseByID';
                this.$axios.get(this.findUserUrl, { params: { id: this.form.courseID } }).then((res) => {
                    if (res.data[res.data.length - 1] != null) {
                        that.$message.error(`课程号已经存在`);
                        this.form.courseID = '';
                    }
                });
            } else {
            }
        },
        handleChange1(value) {
            this.form.coursePeriodB = this.form.coursePeriodF + 1;
            console.log(value);
        },
        handleChange2(value) {
            // console.log(value);
        },
        handleChange3(value) {
            this.form.courseWeekB = this.form.courseWeekF + 1;
        },
        handleChange4(value) {},
        handleChange5(value) {
            // console.log(value);
        },
        onUpload() {
            this.$message.error(`导入未开发完，敬请期待!`);
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
        }
    }
};
</script>

</script>
 
<style scoped>
.perid {
    position: relative;
}
.line {
    margin-left: 120px;
    margin-top: -30px;
    margin-right: 50px;
}
.perid-right {
    margin-left: 30px;
}
</style>