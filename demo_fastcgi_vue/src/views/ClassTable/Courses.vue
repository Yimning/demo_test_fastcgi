<template>
    <div class="course-table">
        <div class="content-title">个人课程表</div>
        <el-scrollbar style="height: 100%">
            <div class="course-table-content">
                <div class="top" :style="{ width: courseWidth * weekTable.length + 'px' }">
                    <div v-for="item in weekTable" :key="item" class="top-text" :style="{ width: courseWidth + 'px' }">星期{{ item }}</div>
                </div>

                <div class="main" :style="{ width: courseWidth * weekTable.length + 'px', height: courseHeight * timeTable.length + 'px' }">
                    <div class="period">
                        <div v-for="item in timeTable" :key="item" class="left-text" :style="{ height: courseHeight + 'px' }">
                            {{ item }}
                        </div>
                    </div>

                    <!--课表-->
                    <!-- class="s" v-for="(item, index) in CourseInfo" :key="'s-' + index" -->
                    <div v-for="(item, index) in CourseInfo" :key="(item, index)">
                        <div
                            class="flex-item kcb-item"
                            @click="
                                selectedCourseIndex = index;
                                showUsualCourseDialog = true;
                            "
                            :style="{
                                marginLeft: (item.courseDay - 1) * courseWidth + 'px',
                                marginTop: (item.coursePeriodF - 1) * courseHeight + 5 + 'px',
                                width: courseWidth + 'px',
                                height: (item.coursePeriodB - item.coursePeriodF) * courseHeight - 5 + 'px',
                                backgroundColor: colorArrays[index % 9]
                            }"
                        >
                            <div class="small-text">{{ item.courseName + '@' + item.classRoomID }}</div>
                        </div>
                    </div>

                    <!-- 遍历对象时,参数： 第一个为值，第二个为键名，第三个为索引 -->
                    <!-- <div class="s" v-for="(item, index) in usualCourses" :key="'s-' + index">
                        <template v-for="(items, key,idx) in item.course">
                             {{ items }}{{key }}{{idx }}
                            <div 
                                v-if="key == 'courseDay'"
                                :key="key"
                                :style="{
                                    marginLeft: (key == 'courseDay' ? item : '1' - 1) * courseWidth + 'px',
                                    marginTop: (key == 'coursePeriodF' ? item : '1' - 1) * courseHeight + 5 + 'px',
                                    width: courseWidth + 'px',
                                    height: 3 * courseHeight - 5 + 'px',
                                    backgroundColor: colorArrays[idx % 9]
                                }"
                            >
                            </div>
                            <div v-if="key == 'courseName'" :key="key">课程:{{ items }}</div>
                        </template>
                    </div> -->

                    <!--事件课显示按钮-->
                    <el-button type="primary" @click="showPracticeCourseDialog = true" class="btn_practice_course">实践课</el-button>
                </div>
            </div>
        </el-scrollbar>

        <el-dialog title="我的实践课" :visible.sync="showPracticeCourseDialog" width="30%" center>
            <el-scrollbar style="height: 500px" wrap-style="overflow-x:hidden;">
                <div class="dialog-content">
                    <div v-for="(item, index) in practiceCourses" :key="(item, index)">
                        <div>课程名称： {{ item.name }}</div>
                        <div>上课教师： {{ item.teacher }}</div>
                    </div>
                    <div class="tip" v-if="practiceCourses.length < 1">本学期没有实践课哦</div>
                </div>
            </el-scrollbar>
        </el-dialog>
        <el-dialog title="课程信息" :visible.sync="showUsualCourseDialog" width="30%" center>
            <div class="dialog-content">
                <div v-if="typeof selectedCourse != 'undefined'">
                    <div>课程名称： {{ selectedCourse.courseName }}</div>
                    <div>
                        上课时间：
                        {{ selectedCourse.courseTime }}
                    </div>
                    <div>
                        课程信息：
                        {{
                            '每周' +
                            selectedCourse.courseDay +
                            ' ' +
                            '第' +
                            selectedCourse.coursePeriodF +
                            '-' +
                            selectedCourse.coursePeriodB +
                            '节'
                        }}
                    </div>

                    <div>上课地点： {{ selectedCourse.classRoomID }}</div>
                    <div>上课教师： {{ selectedCourse.teacherName }}</div>
                    <div>上课周期： {{ selectedCourse.courseWeekF + '-' + selectedCourse.courseWeekB + '周' }}</div>
                </div>
                <div v-else class="tip">本学期没有课哦！</div>
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button type="primary" @click="showUsualCourseDialog = false">确 定</el-button>
                <el-button v-if="isTeacher" type="primary" @click="signIn">进行签到</el-button>
            </span>
        </el-dialog>
    </div>
</template>
 
<script>
const weekArr = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'];
export default {
    name: 'CourseTable',
    props: ['usualCourses'],
    data() {
        return {
            showUsualCourseDialog: false,
            showPracticeCourseDialog: false,
            selectedCourseIndex: 0,
            findUserUrl: '',
            params: {},
            usualCourses: [{}],
            CourseInfo: [{}],
            list: [{}],
            catalogArr: [], //类目数组
            catalogObj: {}, //嵌套对象
            isTeacher: false,
            weeks: {
                0: '星期日',
                1: '星期一',
                2: '星期二',
                3: '星期三',
                4: '星期四',
                5: '星期五',
                6: '星期六'
            },
            dataParams: {}
        };
    },

    props: {
        width: {
            type: Number,
            default: 385
        },
        height: {
            type: Number,
            default: 635
        },

        practiceCourses: {
            type: Array,
            default: () => []
        },
        weekTable: {
            type: Array,
            default: () => ['一', '二', '三', '四', '五', '六', '日']
        },
        timeTable: {
            type: Array,
            default: () => [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
        },
        colorArrays: {
            type: Array,
            default: () => ['#ef5b9c', '#f15b6c', '#f26522', '#ffd400', '#8552a1', '#7fb80e', '#65c294', '#78cdd1', '#33a3dc']
        }
    },
    computed: {
        courseWidth() {
            return Math.max((this.width - 35) / this.weekTable.length, 130);
        },
        courseHeight() {
            return Math.max((this.height - 35) / this.timeTable.length, 35);
        },
        selectedCourse() {
            return this.CourseInfo[this.selectedCourseIndex];
        }
    },
    //数据渲染
    created() {
        //角色判断
        if (this.$store.getters.getUser.roseID == '0') {
            this.findUserUrl = '/api/scourse/findScourseBysIDcIDcD';
            this.params = { params: { sID: this.$store.getters.getUser.userID } };
        } else if (this.$store.getters.getUser.roseID == '1') {
            this.isTeacher = true; //只有教师显示
            this.findUserUrl = '/api/scourse/findScourseBytIDcIDcD';
            this.params = { params: { tID: this.$store.getters.getUser.userID } };
        } else {
        }

        this.$axios
            .get(this.findUserUrl, this.params)
            .then((res) => {
                //console.log(res);
                //this.form = res.data[res.data.length - 1];
                this.usualCourses = res.data;
                console.log(this.usualCourses);
                this.list = [];
                let newArray = [];
                for (const i in res.data) {
                    for (const key in res.data[i].course) {
                        //console.log("属性:"+key);
                        this.$set(this.list, key, res.data[i].course[key]); //对象新增属性(使用Vue.$set())
                        newArray[i] = this.list; //新建数组存放
                        // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                    }
                    for (const key in res.data[i].student) {
                        //console.log("属性:"+key);
                        this.$set(this.list, key, res.data[i].student[key]); //对象新增属性(使用Vue.$set())
                        newArray[i] = this.list; //新建数组存放
                        // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                    }
                    for (const key in res.data[i].teacher) {
                        //console.log("属性:"+key);
                        this.$set(this.list, key, res.data[i].teacher[key]); //对象新增属性(使用Vue.$set())
                        newArray[i] = this.list; //新建数组存放
                        // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                    }
                    this.list = []; //循环完必须清空,否则可能会覆盖
                }
                this.CourseInfo = newArray;
            })
            .catch((err) => {
                console.log(err);
            });
    },
    mounted() {},
    methods: {
        signIn() {
            //获取当前的课程信息
            // console.log(this.selectedCourse);

            //将数组转成对象
            var obj = {};
            for (var i in this.selectedCourse) {
                obj[i] = this.selectedCourse[i];
            }
            this.dataParams = obj;
            //console.log(this.dataParams);
            var aData = new Date();
            //console.log( this.dataDateNumber(aData));//显示当前星期几
            if (this.selectedCourse.courseID == this.dataDateNumber(aData)) {
                sessionStorage.setItem('dataParams', JSON.stringify(this.dataParams));
                this.showUsualCourseDialog = false;
                this.$router.push({ path: '/SignIn', query: { data: this.dataParams } }); //路由跳转传参
            } else {
                this.$confirm('当前课程时间不一致, 是否进行签到?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                })
                    .then(() => {
                        sessionStorage.setItem('dataParams', JSON.stringify(this.dataParams));
                        this.showUsualCourseDialog = false;
                        this.$router.push({ path: '/SignIn', query: { data: this.dataParams } }); //路由跳转传参
                    })
                    .catch(() => {
                        this.showUsualCourseDialog = false;
                        this.$message({
                            type: 'info',
                            message: '已取消'
                        });
                    });
            }
        },
        // 时间格式化
        dataFormat(value) {
            if (value != null || value == '') {
                var year = value.substr(0, 4);
                var month = value.substr(5, 2);
                var day = value.substr(8, 2);
                var hour = value.substr(11, 2);
                var min = value.substr(14, 2);
                var second = value.substr(17, 2);
                return year + '-' + month + '-' + day + ' ' + hour + ':' + min + ':' + second;
            } else return null;
        },
        //根据当前的日期显示当前是星期几
        dataDateChange(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                //this.week = this.weeks[weekIndex];
                return this.weeks[weekIndex];
            } else return null;
        },
        //根据当前的日期显示当前是星期几的索引
        dataDateNumber(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                return weekIndex;
            } else return null;
        },
        GMTToStr: function (time) {
            let date = new Date(time);
            let Str =
                date.getFullYear() +
                '-' +
                (date.getMonth() + 1) +
                '-' +
                date.getDate() +
                ' ' +
                date.getHours() +
                ':' +
                date.getMinutes() +
                ':' +
                date.getSeconds();
            return Str;
        },
        StrToGMT(time) {
            let GMT = new Date(time);
            return GMT;
        }
    }
};
</script>
 
<style scoped>
.content-title {
    font-size: 20px;
    /* justify-content: center; */
    display: flex;
    align-items: center;
    text-align: center;
    padding: 0px 0px 0px 40px;
}
.course-table-content {
    padding: 0px 0px 0px 40px;
}

.course-table {
    border-radius: 12px;
}
.top {
    display: flex;
    flex-direction: row;
    padding-left: 35px;
    height: 60px;
    background-color: #31c27c;
    color: #fff;
}
.top-text {
    padding: 0px 0px 0px 50px;
    width: 100px;
    height: 60px;
    font-size: 25px;
    justify-content: center;
    display: flex;
    align-items: center;
    text-align: center;
}
.main {
    height: 1200px;
    width: 730px;
    display: flex;
    position: relative;
}
.flex-item {
    width: 95px;
    height: 200px;
}
.kcb-item {
    position: absolute;
    justify-content: center;
    display: flex;
    align-items: center;
    border-radius: 12px;
    overflow: hidden;
}
.period {
    background-color: #31c27c;
    color: #fff;
}
.small-text {
    font-size: 22px;
    color: #fff;
    text-align: center;
}
.left-text {
    width: 70px;
    height: 100px;
    font-size: 26px;
    justify-content: center;
    display: flex;
    align-items: center;
}
.btn_practice_course {
    position: absolute;
    z-index: 110;
    top: 35px;
    right: 0px;
    width: 100px;
    height: 100px;
    line-height: 24px;
    background: #31c27c;
    border-radius: 50px;
    font-size: 24px;
    text-align: center;
    color: #fff;
    opacity: 0.7;
    padding: 12px;
}
.el-dialog .dialog-content {
    color: #000;
    line-height: 60px;
}
.el-dialog .dialog-content .tip {
    color: #000;
    line-height: 60px;
    text-align: center;
}
</style>