<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i> 用户信息管理 </el-breadcrumb-item>
                <el-breadcrumb-item>个人信息</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="form-box">
                <el-form ref="form" :model="form" label-width="80px">
                    <el-card class="box-card" v-if="roseID == '0'">
                        <div slot="header" class="clearfix">
                            <span>{{ form.studentName }}</span>
                            <el-button style="float: right; padding: 3px 0" type="text" @click="refresh">刷新</el-button>
                        </div>
                        <div class="items">
                            <div class="item text">
                                {{ '性别: ' + form.studentSex }}
                            </div>
                            <div class="item text">
                                {{ '出生年月:' + form.studentBirth }}
                            </div>
                            <div class="item text">
                                {{ '班级: ' + form.studentClass }}
                            </div>
                            <div class="item text">
                                {{ '专业: ' + form.profession }}
                            </div>
                            <div class="item text">
                                {{ '身份号码:' + form.cardNo }}
                            </div>
                            <div class="item text">
                                {{ '角色:' + form.roseName }}
                            </div>
                        </div>
                    </el-card>
                    <el-card class="box-card" v-else-if="roseID == '1'">
                        <div slot="header" class="clearfix">
                            <span>{{ form.teacherName }}</span>
                            <el-button style="float: right; padding: 3px 0" type="text" @click="refresh">刷新</el-button>
                        </div>
                        <div class="items">
                            <div class="item text">
                                {{ '性别: ' + form.teacherSex }}
                            </div>
                            <div class="item text">
                                {{ '出生年月:' + form.teacherBirth }}
                            </div>

                            <div class="item text">
                                {{ '身份号码:' + form.cardNo }}
                            </div>
                            <div class="item text">
                                {{ '所授课程号: ' + form.courseID }}
                            </div>
                            <div class="item text">
                                {{ '角色:' + form.roseName }}
                            </div>
                        </div>
                    </el-card>
                    <el-card class="box-card" v-else>
                        <div slot="header" class="clearfix">
                            <span>{{ form.adminName }}</span>
                            <el-button style="float: right; padding: 3px 0" type="text" @click="refresh">刷新</el-button>
                        </div>
                        <div class="items">
                            <div class="item text">
                                {{ '性别: ' + form.adminSex }}
                            </div>
                            <div class="item text">
                                {{ '出生年月:' + form.adminBirth }}
                            </div>
                            <div class="item text">
                                {{ '身份号码:' + form.cardNo }}
                            </div>
                            <div class="item text">
                                {{ '角色:' + form.roseName }}
                            </div>
                        </div>
                    </el-card>
                </el-form>
                <el-row>
                    <el-col class="card-content" :span="8" v-for="(o, index) in 1" :key="o" :offset="index > 0 ? 2 : 0">
                        <el-card :body-style="{ padding: '0px' }">
                            <img
                                :src="form.face"
                                class="image"
                            />
                            <div style="padding: 14px">
                                <span>个人头像</span>
                                <div class="bottom clearfix">
                                    <time class="time">{{ currentDate }}</time>
                                    <!-- <el-button type="text" class="button">操作按钮</el-button> -->
                                </div>
                            </div>
                        </el-card>
                    </el-col>
                </el-row>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'personInfo',
     inject: ['reload'],
    data() {
        return {
            currentDate: new Date(),
            form: {},
            roseID: this.$store.getters.getUser.roseID
        };
    }, 
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
            })
            .catch((err) => {
                console.log(err);
            });
    },
    methods: {
        refresh() {
          this.reload(); //刷新 ----推荐
        }
        //  或者使用做个地址请求 '/api/student/findStudentByID?id=1'
    }
};
</script>



<style>
.text {
    font-size: 14px;
}

.item {
    margin-bottom: 18px;
}
.items {
    display: flex;
    flex-direction: column;
    justify-content: center;
}

.clearfix:before,
.clearfix:after {
    display: table;
    content: '';
}
.clearfix:after {
    clear: both;
}

.card-content {
    padding: 0 100px 0 0 ;
    position: relative;
    margin-top: -248px;
    margin-left: 700px;
    margin-bottom: 100px;
}

.box-card {
    width: 480px;
    margin-left: 200px;
}

.time {
    font-size: 13px;
    color: #999;
}

.bottom {
    margin-top: 13px;
    line-height: 12px;
}

.button {
    padding: 0;
    float: right;
}

.image {
    width: 100%;
    display: block;
}

.clearfix:before,
.clearfix:after {
    display: table;
    content: '';
}

.clearfix:after {
    clear: both;
}
</style>