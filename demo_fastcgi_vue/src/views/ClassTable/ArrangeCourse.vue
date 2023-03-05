<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i> 课程管理 </el-breadcrumb-item>
                <el-breadcrumb-item>排课</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <el-button type="info" icon="el-icon-download" @click="onUpload">外部导入</el-button>
            <div class="form-box">
                <el-form ref="form" :model="form" :rules="rules" label-width="280px" class="box-content">
                    <el-form-item label="课程号:" prop="courseID">
                        <el-select v-model="form.courseID" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.options"
                                :key="item.courseID"
                                :label="item.courseID"
                                :value="item.courseID"
                            ></el-option>
                        </el-select>
                    </el-form-item>

                    <el-form-item label="课程名称:" prop="courseName">
                        <el-select v-model="form.courseID" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.options"
                                :key="item.courseID"
                                :label="item.courseName"
                                :value="item.courseID"
                            ></el-option>
                        </el-select>
                    </el-form-item>

                    <el-form-item label="教师号:" prop="teacherNumber">
                        <el-select v-model="form.teacherNumber" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.teacherOptions"
                                :key="item.teacherNumber"
                                :label="item.teacherNumber"
                                :value="item.teacherNumber"
                            ></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="授课教师:" prop="teacherName">
                        <el-select v-model="form.teacherNumber" placeholder="请选择">
                            <el-option
                                @change="handleChange5"
                                el-option
                                v-for="item in form.teacherOptions"
                                :key="item.teacherNumber"
                                :label="item.teacherName"
                                :value="item.teacherNumber"
                            ></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="班级号:" prop="studentClass">
                        <el-select v-model="form.studentNumber" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.studentOptions"
                                :key="item.studentNumber"
                                :label="item.studentClass"
                                :value="item.studentNumber"
                            ></el-option>
                        </el-select>
                    </el-form-item>

                    <el-form-item label="学号:" prop="studentNumber">
                        <el-select v-model="form.studentNumber" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.studentOptions"
                                :key="item.studentNumber"
                                :label="item.studentNumber"
                                :value="item.studentNumber"
                            ></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="学生姓名:" prop="studentName">
                        <el-select v-model="form.studentNumber" placeholder="请选择">
                            <el-option
                                el-option
                                v-for="item in form.studentOptions"
                                :key="item.studentNumber"
                                :label="item.studentName"
                                :value="item.studentNumber"
                            ></el-option>
                        </el-select>
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
                    <span style="font-size: 18px">课程已添加！{{ Sencond }}秒后关闭页面,并刷新。</span>
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
                teacherOptions: [],
                studentOptions: [],
                coursePeriodF: 1,
                coursePeriodB: 3,
                courseWeekF: 1,
                courseWeekB: 18
            },
            findUserUrl: '',
            updateOneUrl: '',
            rules: {
                courseID: [{ required: true, message: '必填', trigger: 'blur' }],
                //   courseName: [{ required: true, message: '必填', trigger: 'blur' }],
                teacherNumber: [{ required: true, message: '必填', trigger: 'blur' }],
                //   teacherName: [{ required: true, message: '必填', trigger: 'blur' }],
                //  studentClass: [{ required: true, message: '必填', trigger: 'blur' }],
                studentNumber: [{ required: true, message: '必填', trigger: 'blur' }]
                // studentName: [{ required: true, message: '必填', trigger: 'blur' }]
            },
            Successdialog: false, //控制弹出
            Sencond: 5, //设置初始倒计时
            isDisabled: false
        };
    },
    //  或者使用做个地址请求 '/api/student/findStudentByID?id=1'
    created() {
        const that = this;
        this.findUserUrl = '/api/course/findAllCourse';
        this.updateOneUrl = '/api/scourse/add';

        var r0 = this.$axios.get(this.findUserUrl);
        var r1 = this.$axios.get('/api/student/findAllStudent');
        var r2 = this.$axios.get('/api/teacher/findAllTeacher');
        //并发请求
        if (this.$store.getters.getUser.roseName == '教师管理员') {
            this.$axios
                .all([r0, r1, r2])
                .then(
                    that.$axios.spread((res1, res2, res3) => {
                        // console.log(res1);
                        that.form.options = res1.data;
                        // console.log(res2);
                        that.form.studentOptions = res2.data;
                        //console.log(res3);
                        that.form.teacherOptions = res3.data;
                    })
                )
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
                    this.$confirm('确定操作?', '提示', {
                        confirmButtonText: '确定',
                        cancelButtonText: '取消',
                        type: 'info'
                    })
                        .then(() => {
                            that.$axios
                                .post(that.updateOneUrl, that.form)
                                .then((res) => {   
                                   // console.log(res);
                                    if (res.data === 'exist') return that.$message.error(`选课已存在`);
                                    if (res.data === 'success') return that.$message.success(`选课成功`);
                                    if (res.data === 'fail') return that.$message.error(`选课失败`);
                                    // that.addAttendance(that.form);
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
        },
        addAttendance(data) {
            const that = this;
            const url = '/api/attendance/add';
            console.log(data);
            //data={recordID:11,studentNumber:"fff"};
            this.$axios
                .post(url, data)
                .then((res) => {
                    console.log(res);
                })
                .catch((err) => {
                    console.error();
                });
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