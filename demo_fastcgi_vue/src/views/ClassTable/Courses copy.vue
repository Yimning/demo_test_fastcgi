<template>
    <div class="course-table">
        <el-scrollbar style="height: 100%">
            <div class="course-table-content">
                <div class="top" :style="{ width: courseWidth * weekTable.length + 'px' }">
                    <div v-for="item in weekTable" :key="item" class="top-text" :style="{ width: courseWidth + 'px' }">周{{ item }}</div>
                </div>

                <div
                    class="main"
                    :style="{ width: courseWidth * weekTable.length + 35 + 'px', height: courseHeight * timeTable.length + 'px' }"
                >
                    <div class="period">
                        <div v-for="item in timeTable" :key="item" class="left-text" :style="{ height: courseHeight + 'px' }">
                            {{ item }}
                        </div>
                    </div>

                    <!--课表-->
                    <div v-for="(item, index) in usualCourses" :key="(item, index)">
                        <div
                            class="flex-item kcb-item"
                            @click="
                                selectedCourseIndex = index;
                                showUsualCourseDialog = true;
                            "
                            :style="{
                                marginLeft: (item.day - 1) * courseWidth + 'px',
                                marginTop: (item.period - 1) * courseHeight + 5 + 'px',
                                width: courseWidth + 'px',
                                height: item.length * courseHeight - 5 + 'px',
                                backgroundColor: colorArrays[index % 9]
                            }"
                        >
                            <div class="small-text">{{ item.name + '@' + item.room }}</div>
                        </div>
                    </div>
 
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
                    <div>课程名称： {{ selectedCourse.name }}</div>
                    <div>
                        上课时间：
                        {{
                            selectedCourse.week +
                            ' ' +
                            '第' +
                            selectedCourse.period +
                            '-' +
                            (Number(selectedCourse.period) + Number(selectedCourse.length) - 1) +
                            '节'
                        }}
                    </div>
                    <div>上课教师： {{ selectedCourse.teacher }}</div>
                    <div>上课地点： {{ selectedCourse.room }}</div>
                </div>
                <div v-else class="tip">本学期没有课哦</div>
            </div>
            <span slot="footer" class="dialog-footer">
                <el-button type="primary" @click="showUsualCourseDialog = false">确 定</el-button>
            </span>
        </el-dialog>
    </div>
</template>
 
<script>
export default {
    name: 'CourseTable',
    data() {
        return {
            showUsualCourseDialog: false,
            showPracticeCourseDialog: false,
            selectedCourseIndex: 0
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
        // usualCourses: {
        //     type: Array,
        //     default: () => [
        //         {
        //             day: '1',
        //             length: '3',
        //             name: '普通物理A2',
        //             period: '3-5节',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '3',
        //             length: '3',
        //             name: '普通物理A2',
        //             period: '6',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '3',
        //             length: '3',
        //             name: '普通物理A2',
        //             period: '3',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '3',
        //             length: '2',
        //             name: '普通物理A2',
        //             period: '1',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '2',
        //             length: '2',
        //             name: '普通物理A2',
        //             period: '1',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '4',
        //             length: '2',
        //             name: '普通物理A2',
        //             period: '1',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         },
        //         {
        //             day: '5',
        //             length: '2',
        //             name: '普通物理A2',
        //             period: '1',
        //             room: '2-N219',
        //             teacher: '祝华',
        //             type: '一般课',
        //             week: '1-16周'
        //         }
        //     ]
        // },
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
            return Math.max(this.width / this.weekTable.length, 130);
        },
        courseHeight() {
            return Math.max(this.height / this.timeTable.length, 50);
        },
        selectedCourse() {
            return this.usualCourses[this.selectedCourseIndex];
        }
    },
    created() {
        this.findUserUrl = '/api/scourse/findScourseBystudentNumber';
        this.$axios
            .get(this.findUserUrl, { params: { studentNumber: this.$store.getters.getUser.userID } })
            .then((res) => {
                // console.log(res);
                //this.form = res.data[res.data.length - 1];
                this.props.usualCourses = res.data;
                console.log(this.props.usualCourses);
            })
            .catch((err) => {
                console.log(err);
            });
    },
    mounted() {},
    methods: {}
};
</script>
 
<style scoped>
.course-table-content {
    padding: 20px 0px 0px 20px;
}

.course-table {
    border-radius: 12px;
}
.top {
    display: flex;
    flex-direction: row;
    padding-left: 35px;
    background-color: #31c27c;
    color: #fff;
}
.top-text {
    width: 100px;
    height: 35px;
    font-size: 26px;
    justify-content: center;
    display: flex;
    align-items: center;
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
    width: 35px;
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